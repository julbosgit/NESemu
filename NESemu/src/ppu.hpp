//
//  ppu.hpp
//
//  Created 1/1/21.
//

#ifndef ppu_hpp
#define ppu_hpp

#include "iobus.hpp"
#include <SDL.h>

const uint32_t RGBA_SYSTEM_COLORS[] = {
    0x666666ff, 0x002a88ff, 0x1412a7ff, 0x3b00a4ff, 0x5c007eff, 0x6e0040ff, 0x6c0600ff, 0x561d00ff,
    0x333500ff, 0x0b4800ff, 0x005200ff, 0x004f08ff, 0x00404dff, 0x000000ff, 0x000000ff, 0x000000ff,
    0xadadadff, 0x155fd9ff, 0x4240ffff, 0x7527feff, 0xa01accff, 0xb71e7bff, 0xb53120ff, 0x994e00ff,
    0x6b6d00ff, 0x388700ff, 0x0c9300ff, 0x008f32ff, 0x007c8dff, 0x000000ff, 0x000000ff, 0x000000ff,
    0xfffeffff, 0x64b0ffff, 0x9290ffff, 0xc676ffff, 0xf36affff, 0xfe6eccff, 0xfe8170ff, 0xea9e22ff,
    0xbcbe00ff, 0x88d800ff, 0x5ce430ff, 0x45e082ff, 0x48cddeff, 0x4f4f4fff, 0x000000ff, 0x000000ff,
    0xfffeffff, 0xc0dfffff, 0xd3d2ffff, 0xe8c8ffff, 0xfbc2ffff, 0xfec4eaff, 0xfeccc5ff, 0xf7d8a5ff,
    0xe4e594ff, 0xcfef96ff, 0xbdf4abff, 0xb3f3ccff, 0xb5ebf2ff, 0xb8b8b8ff, 0x000000ff, 0x000000ff
    
};

class PPU {

    const uint16_t NAME_TABLE_OFFSET = 0x400;
    const uint16_t NAME_TABLE_0 = 0x2000;
    const uint16_t NAME_TABLE_1 = 0x2400;
    const uint16_t NAME_TABLE_2 = 0x2800;
    const uint16_t NAME_TABLE_3 = 0x2C00;
    const uint16_t ATTR_TABLE_OFFSET = 0x3C0;
    const uint16_t PALETTE_ADDR = 0x3F00;
    const uint16_t NUM_TILES_PER_PAGE = 256;
    const uint16_t NUM_TILES          = 2 * NUM_TILES_PER_PAGE;
   
    enum class BGcolor {
        black=0,
        blue=1,
        green=2,
        red=4
    };
    
public:
    
    PPU(std::shared_ptr<IOBus> iob): _iob{iob}, _currentNameTable{NAME_TABLE_0},
                                                _writeIncrements{1},
                                                _spritePatternTableAddr{0},
                                                _screenPatternTableAddr{0},
                                                _spriteSize{0},
                                                NMI_output{true},
                                                NMI_occured{false},
                                                _imageMask{0},
                                                _spriteMask{true},
                                                _showSprite{true},
                                                _showBG{true},
                                                _bgColor{0},
                                                _addrLow{true},
                                                _ppuCycles{0},
                                                _ppuScanline{0},
                                                _camPositionX{0},
                                                _camPositionY{0},
                                                _scrollX{true}
    {       
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
        }
    }
    
    void PPU_step();
    
    //Callbacks mapped to CPU address space
    //Addresses written to by the program
    void control(uint8_t ctrl);
    void setMask(uint8_t mask);
    void setOAMAddress(uint8_t addr);
    void setDataAddress(uint8_t addr);
    void setScroll(uint8_t scroll);
    void setData(uint8_t data);
    void DMA(uint8_t n);
    //Read by the program
    uint8_t getStatus();
    uint8_t getData();
    uint8_t getOAMData();
    void setOAMData(uint8_t value);
    
    bool getNMI();
    void initGameWindow();
    

    
    
private:

    enum PPURegisters {
        PPUCR1 = 0x2000,
        PPUCR2 = 0x2001,
        PPUSR  = 0x2002,
        PPUSMA = 0x2003,
        PPUSMD = 0x2004,
        PPUSSO = 0x2005,
        PPUADR = 0x2006,
        PPUDTA = 0x2007,
        PPUDMA = 0x4014
    };
    
    const uint16_t SCREEN_W = 256;
    const uint16_t SCREEN_H = 240;
    uint32_t _pixels[256*240];
    

    std::shared_ptr<IOBus> _iob;
    
    // PPU Control register 1 variables
    uint16_t _currentNameTable;
    uint8_t _writeIncrements; // +1 or +32
    uint16_t _spritePatternTableAddr;
    uint16_t _screenPatternTableAddr;
    uint8_t _spriteSize; //8x8 or 8x16
    bool NMI_output;
    
    // PPU Control register 2 variables
    bool _imageMask;
    bool _spriteMask;
    bool _showBG;
    bool _showSprite;
    uint8_t _bgColor;
    
    
    std::bitset<8> _PPUSR;
    
    uint16_t _spriteAddr;
    uint8_t _spriteData;
    
    bool _addrLow;
    uint16_t _PPUAddrTMP;
    uint16_t _PPUAddr;
    uint8_t _PPUData;
    uint8_t _dataBuffer;
    
    uint8_t _DMACPUtoSprite;
    
    // Scroll register
    bool _scrollX;
    uint8_t _camPositionX;
    uint8_t _camPositionY;
    
    
    std::array<uint8_t, 256> _SpriteMemory;
    
    
    uint32_t _ppuCycles;
    uint16_t _ppuScanline;
    // Info on https://wiki.nesdev.com/w/index.php/NMI
    bool NMI_occured;
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    
    void _drawWindow();
    void _displayPatternTables();
    void _displayNameTables(uint16_t nameTableAddr);
    void _displayNameTables(uint16_t nameTableAddr, uint8_t, uint8_t, int16_t);
    void _displaySprites();
    
};

#endif /* ppu_hpp */
