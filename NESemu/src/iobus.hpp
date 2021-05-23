//
//  iobus.hpp
//
//  Created 12/30/20.
//

#ifndef iobus_hpp
#define iobus_hpp

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include "cartridge.hpp"

enum IORegisters
{
    PPUCTRL = 0x2000,
    PPUMASK,
    PPUSTATUS,
    OAMADDR,
    OAMDATA,
    PPUSCROL,
    PPUADDR,
    PPUDATA,
    OAMDMA = 0x4014,
    JOY1 = 0x4016,
    JOY2 = 0x4017,
};

class IOBus {
        
private:
    std::array<uint8_t, 0x2000> _RAM;
    std::array<uint8_t, 0x2000> _VRAM;
    
    Cartridge *c;
    const uint16_t UPPER_RAM_ADDR = 0x1FFF;
    const uint16_t UPPER_PPU_ADDR = 0x3FFF;
    
    const uint16_t LOWER_BANK_ROM = 0x8000;
    const uint16_t UPPER_BANK_ROM = 0xC000;
    
    const uint16_t PPU_UPPER_PATTERN_0 = 0x1000;
    const uint16_t PPU_UPPER_PATTERN_1 = 0x2000;
    
    const uint16_t LOWER_VRAM = 0x2000;
    const uint16_t UPPER_VRAM = 0x3FFF;
    
    std::map<IORegisters, std::function<void(uint8_t)>> m_writeCallbacks;
    std::map<IORegisters, std::function<uint8_t(void)>> m_readCallbacks;
    
    
    
public:
    IOBus(Cartridge *c): c{c}
    {}
   
    uint8_t readMemory(uint16_t addr);

    void writeMemory(uint16_t addr, uint8_t value);

    
    inline uint8_t PPUreadMemory(uint16_t addr)
    {
        if(addr < LOWER_VRAM)
            return c->PPUreadMemory(addr);
        
        if(addr == 0x3F10)
            addr = 0x3F00;
        else if (addr == 0x3F14)
            addr = 0x3F04;
        else if (addr == 0x3F18)
            addr = 0x3F08;
        else if (addr == 0x3F1C)
            addr = 0x3F0C;
        
        return _VRAM[addr % (UPPER_VRAM - LOWER_VRAM + 1)];
         
         return c->PPUreadMemory(addr);
    }
       
    inline void PPUwriteMemory(uint16_t addr, uint8_t value)
    {
        if(addr < LOWER_VRAM) {
   //         std::cout << "Cannot write to CHR ROM - address: " << std::hex << addr << std::endl;
   //         return;
            c->PPUwriteMemory(addr, value);
        }
        else {
            // Mirroring https://wiki.nesdev.com/w/index.php/PPU_palettes
            if(addr == 0x3F10)
                addr = 0x3F00;
            else if (addr == 0x3F14)
                addr = 0x3F04;
            else if (addr == 0x3F18)
                addr = 0x3F08;
            else if (addr == 0x3F1C)
                addr = 0x3F0C;
            _VRAM[addr % (UPPER_VRAM - LOWER_VRAM + 1)] = value;
        }
    }

    bool setWriteCallback(IORegisters, std::function<void(uint8_t)> );
    bool setReadCallback(IORegisters, std::function<uint8_t(void)> );
    bool setNMICallback(std::function<bool(void)> );
    bool setDMACPUCallback(std::function<void(void)> );
    std::function<bool(void)> m_NMICallback;
    std::function<void(void)> m_DMACPUCallback;
    
};


#endif /* iobus_hpp */
