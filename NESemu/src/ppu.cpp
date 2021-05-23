//
//  ppu.cpp
//
//  Created 1/1/21.
//

#include "ppu.hpp"
#include <iostream>
#include <fstream>

bool NMIDONE = false;

static uint8_t scroll_x = 0;
static uint16_t first_name_table = 0x2000;//PPU::NAME_TABLE_0;
static uint16_t second_name_table = 0x2400;//PPU::NAME_TABLE_1;

void PPU::PPU_step()
{
    _ppuCycles++;
    
    if (_ppuCycles > 340) {
        _ppuCycles -= 341;
        _ppuScanline++;
    }
    
    
    if((_ppuCycles == 3) && (_ppuScanline == 1)) {
        // generate a sprite 0 hit, some games use it for timing - this is fake though, not taking the real sprite 0 condition
        // http://wiki.nesdev.com/w/images/d/d1/Ntsc_timing.png
        _PPUSR.set(6);
    }
            
       
    if (0 <= _ppuScanline && _ppuScanline <= 239) {
  //      SDL_UpdateWindowSurface( window );
    }
    else if (_ppuScanline == 241 && _ppuCycles == 1) {    //  VBlank
        _PPUSR.set(7);
        _PPUSR.reset(6);
        NMI_occured = true;
        
        if(NMIDONE) {
            scroll_x = _camPositionX;
            NMIDONE = false;
            
            if(first_name_table != _currentNameTable)
                std::swap(first_name_table, second_name_table);
        }
        
            
        if(_showBG) {
            _displayNameTables(first_name_table, scroll_x, SCREEN_W-1, -scroll_x); // vertical mirroring and scrollY not implemented
            _displayNameTables(second_name_table, 0, scroll_x, (SCREEN_W - 1 - scroll_x));

        }
        if(_showSprite)
            _displaySprites();
        
        _drawWindow();
    }
    else if (_ppuScanline == 261 && _ppuCycles == 1) {    //  VBlank off / pre-render line

        _PPUSR.reset(6);
        _PPUSR.reset(7);
        NMI_occured = false;
        _ppuScanline = 0;
    }
}

void PPU::control(uint8_t val)
{
    _currentNameTable = NAME_TABLE_0 + (val&0x03)*NAME_TABLE_OFFSET;
    _writeIncrements = 1 + 31*((val&0x04) >> 2); // +1 or +32
    _spritePatternTableAddr = 0x1000 * ((val&0x08) >> 3);
    _screenPatternTableAddr = 0x1000 * ((val&0x10) >> 4);
    _spriteSize = 8 + 8 *  ((val&0x40) >> 6); //8x8 or 8x16
    NMI_output = (val&0x80) == 0x80;
}

void PPU::setMask(uint8_t val)
{
    _imageMask = (val & 0x02) == 0;
    _spriteMask = (val & 0x04) == 0;;
    _showBG = (val & 0x08);
    _showSprite = (val & 0x10);
    _bgColor = (val & 0xE0) >> 5 ;
}

uint8_t PPU::getStatus()
{
    uint8_t oldState = static_cast<uint8_t>(_PPUSR.to_ulong());
    // clear VBlank
    _PPUSR.reset(7);
    
    return oldState;
}

void PPU::setDataAddress(uint8_t addr)
{
    if (_addrLow)
    {
        _PPUAddrTMP = addr;
        _addrLow = false;
    }
    else
    {
        _PPUAddr = ((_PPUAddrTMP & 0x3F) << 8) | addr;
        _addrLow = true;
    }
}

uint8_t PPU::getData()
{
    auto data = _iob->PPUreadMemory(_PPUAddr);
    _PPUAddr += _writeIncrements;

    //Reads are delayed by one uint8_t/read when address is in this range
    if (_PPUAddr < 0x3f00)
    {
        //Return from the data buffer and store the current value in the buffer
        std::swap(data, _dataBuffer);
    }

    return data;
}

uint8_t PPU::getOAMData()
{
    return _SpriteMemory[_spriteAddr++];
}

void PPU::setData(uint8_t data)
{
    _iob->PPUwriteMemory(_PPUAddr, data);
    _PPUAddr += _writeIncrements;
}

void PPU::setOAMAddress(uint8_t addr)
{
    _spriteAddr = addr;
}

void PPU::setOAMData(uint8_t value)
{
    _SpriteMemory[_spriteAddr++] = value;
}

bool PPU::getNMI()
{
    bool NMI = NMI_output & NMI_occured;
    NMI_occured = false;
    return (NMI);
}

void PPU::DMA(uint8_t n)
{
    for (int i=0 ; i<_SpriteMemory.size() ; i++)
        _SpriteMemory[i] = _iob->readMemory(_SpriteMemory.size()*n + i);
    
    _iob->m_DMACPUCallback();
}

void PPU::setScroll(uint8_t scroll)
{
    if (_scrollX) {
        _camPositionX = scroll;
        _scrollX = false;
    }
    else {
        _camPositionY = scroll;
        _scrollX = true;
    }
}


void PPU::_displayPatternTables()
{
    uint16_t w=128, h=256;
    uint32_t colors[4] = {0x141414FF, 0xDA2B01FF, 0xFF9B3BFF, 0x8B7300FF};
    
    SDL_Window *window = SDL_CreateWindow("NESemu",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       w, h, SDL_WINDOW_RESIZABLE);
    if(window == nullptr)
        std::cout << "Could not create window! SDL_Error: " << SDL_GetError();
    else
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);

        // Format described in http://wiki.nesdev.com/w/index.php/PPU_pattern_tables
        uint32_t pixels[w * h];
        for(int t=0 ;t<NUM_TILES ; t++) {
            for(int line=0 ; line<8 ; line++) {
                uint16_t adr = t*16 + line;
                uint8_t plane[2];
                plane[0] = _iob->PPUreadMemory(adr);
                plane[1] = _iob->PPUreadMemory(adr + 8);
                for(int pix=0 ; pix < 8 ; pix++) {
                    uint8_t pixel = ((plane[0] >> (7-(pix % 8))) & 1) + ((plane[1] >> (7-(pix % 8))) & 1) * 2;
                    uint16_t idx = (t * 8) % w + (static_cast<uint16_t>((t*8) / w)) * w * 8 + w * line + pix ;
                    pixels[idx] = colors[pixel];
                }
            }
        }
      
        SDL_SetRenderTarget(renderer, texture);
        
        SDL_UpdateTexture(texture, nullptr, pixels,w*sizeof(uint32_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while (1) {
            SDL_PollEvent(&e);
            if(e.type == SDL_QUIT) break;
        }
    }
}


void PPU::_displayNameTables(uint16_t nameTableAddr)
{
    uint16_t adr;

//        std::ofstream myfile;
//        myfile.open ("example.txt", std::ios::out | std::ios::app);
//        myfile << "\n\n\n\n " << nameTableAddr << "\n\n\n\n";
    
    for(int k=0 ;k<30 ; k++) {
        for(int t=0 ; t<32 ; t++) {
            uint16_t tile_number = _iob->PPUreadMemory(nameTableAddr + t + k*32);
            uint16_t attr_table_idx = (t / 4) + (k / 4) * 8;
            uint16_t attr_byte = _iob->PPUreadMemory(nameTableAddr + ATTR_TABLE_OFFSET + attr_table_idx);
            uint16_t pallet_num = (t % 4) / 2 + 2 * ((k % 4)/2);
            uint16_t pallet_idx = (attr_byte >> (2 * pallet_num)) & 0x03;
            
            
//                myfile << std::setw(4);
//                myfile << std::hex << tile_number << " ";
            for(int line=0 ; line<8 ; line++) {
                adr =  _screenPatternTableAddr + tile_number*16 + line;
                uint8_t plane[2];
                plane[0] = _iob->PPUreadMemory(adr);
                plane[1] = _iob->PPUreadMemory(adr + 8);
                for(int pix=0 ; pix < 8 ; pix++) {
                    uint8_t pixel = ((plane[0] >> (7-(pix % 8))) & 1) + ((plane[1] >> (7-(pix % 8))) & 1) * 2;

                    uint16_t idx = (t * 8 ) % SCREEN_W + (SCREEN_W * line) + (k*8)*SCREEN_W + pix;
                    if (pixel != 0)
                        _pixels[idx] = RGBA_SYSTEM_COLORS[_iob->PPUreadMemory(PALETTE_ADDR+4*pallet_idx+pixel)];
                    else
                        _pixels[idx] = RGBA_SYSTEM_COLORS[_iob->PPUreadMemory(PALETTE_ADDR)];
                }
            }
        }
//             myfile << "\n";
    }
//        myfile.close();
}


void PPU::_displayNameTables(uint16_t nameTableAddr, uint8_t startX, uint8_t endX, int16_t scrollX)
{
    uint16_t adr;

//        std::ofstream myfile;
//        myfile.open ("example.txt", std::ios::out | std::ios::app);
//        myfile << "\n\n\n\n " << nameTableAddr << "\n\n\n\n";
    
    for(int k=0 ;k<30 ; k++) {
        for(int t=0 ; t<32 ; t++) {
            uint16_t tile_number = _iob->PPUreadMemory(nameTableAddr + t + k*32);
            uint16_t attr_table_idx = (t / 4) + (k / 4) * 8;
            uint16_t attr_byte = _iob->PPUreadMemory(nameTableAddr + ATTR_TABLE_OFFSET + attr_table_idx);
            uint16_t pallet_num = (t % 4) / 2 + 2 * ((k % 4)/2);
            uint16_t pallet_idx = (attr_byte >> (2 * pallet_num)) & 0x03;
            
            
//                myfile << std::setw(4);
//                myfile << std::hex << tile_number << " ";
            for(int line=0 ; line<8 ; line++) {
                adr =  _screenPatternTableAddr + tile_number*16 + line;
                uint8_t plane[2];
                plane[0] = _iob->PPUreadMemory(adr);
                plane[1] = _iob->PPUreadMemory(adr + 8);
                for(int pix=0 ; pix < 8 ; pix++) {
                    uint8_t pixel = ((plane[0] >> (7-(pix % 8))) & 1) + ((plane[1] >> (7-(pix % 8))) & 1) * 2;

                    uint8_t pix_xpos = (t * 8 ) % SCREEN_W + pix;
                    if( (pix_xpos >= startX) && (pix_xpos < endX) ) {
                        uint16_t idx = pix_xpos + scrollX + (SCREEN_W * line) + (k*8)*SCREEN_W;
                        if (pixel != 0)
                            _pixels[idx] = RGBA_SYSTEM_COLORS[_iob->PPUreadMemory(PALETTE_ADDR+4*pallet_idx+pixel)];
                        else
                            _pixels[idx] = RGBA_SYSTEM_COLORS[_iob->PPUreadMemory(PALETTE_ADDR)];
                    }
                }
            }
        }
//             myfile << "\n";
    }
//        myfile.close();
}


void PPU::_displaySprites()
{
    uint16_t adr;
    // going backwards because lower idx sprites have drawing priority in case of overlap
    for(int s=static_cast<int>(_SpriteMemory.size() / 4 - 1) ; s >= 0 ; s--) {
            uint8_t sprite_ypos = _SpriteMemory[s*4];
            uint8_t sprite_idx = _SpriteMemory[s*4 + 1]; // Does not support 8x16 sprites, need to check bit 0 for these
            uint8_t sprite_attr = _SpriteMemory[s*4 + 2];
            uint8_t sprite_xpos = _SpriteMemory[s*4 + 3];
            
            uint16_t pallet_num = sprite_attr & 0x03;
            if (sprite_attr & 0x20) {
                // sprite is behind background, do not show
                continue;
            }
            if ((sprite_ypos > SCREEN_H - 8 - 1) || (sprite_xpos > SCREEN_W - 8 - 1)) {
                // off screen
                continue;
            }
            for(int line=0 ; line<8 ; line++) {
                adr =  _spritePatternTableAddr + sprite_idx*16 + line;
                uint8_t plane[2];
                uint16_t idx;
                plane[0] = _iob->PPUreadMemory(adr);
                plane[1] = _iob->PPUreadMemory(adr + 8);
                for(int pix=0 ; pix < 8 ; pix++) {
                    uint8_t pixel;
                    if(sprite_attr & 0x40) // flip horizontally
                        pixel = ((plane[0] >> ((pix % 8))) & 1) + ((plane[1] >> ((pix % 8))) & 1) * 2;
                    else
                        pixel = ((plane[0] >> (7-(pix % 8))) & 1) + ((plane[1] >> (7-(pix % 8))) & 1) * 2;
                    if(sprite_attr & 0x80) // flip vertically
                        idx = (sprite_xpos) % SCREEN_W + (SCREEN_W * (7-line)) + (sprite_ypos + 1) * SCREEN_W + pix; // y+1
                    else
                        idx = (sprite_xpos) % SCREEN_W + (SCREEN_W * line) + (sprite_ypos + 1) * SCREEN_W + pix; // y+1
                    if (pixel != 0) {
                        // +4 for sprite palette
                        _pixels[idx] = RGBA_SYSTEM_COLORS[_iob->PPUreadMemory(PALETTE_ADDR+4*(4+pallet_num)+pixel)];
                        // transparent if 0 -> don't draw
                    }
                        
                }
            }
        }
}


void PPU::initGameWindow()
{
        uint16_t w=256, h=240;
     window = SDL_CreateWindow("NESemu",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       w, h, SDL_WINDOW_RESIZABLE);
    if(window == nullptr)
        std::cout << "Could not create window! SDL_Error: " << SDL_GetError();
    else
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    }
    SDL_SetWindowSize(window, w, h);
}

void PPU::_drawWindow()
{
    if(window == nullptr) {
        std::cout << "Could not create window! SDL_Error: " << SDL_GetError();
    }
    else
    {
        SDL_SetRenderTarget(renderer, texture);
        
        SDL_UpdateTexture(texture, nullptr, _pixels, SCREEN_W*sizeof(uint32_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}
