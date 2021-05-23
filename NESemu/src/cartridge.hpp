//
//  cartridge.hpp
//
//  Created 12/28/20.
//

#ifndef cartridge_hpp
#define cartridge_hpp

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

class Cartridge {

private:
    std::vector<uint8_t> m_PRG_ROM;
    std::vector<uint8_t> m_CHR_ROM;
    uint8_t m_nameTableMirroring;
    uint8_t m_mapperNumber;
    bool m_extendedRAM;
    bool m_chrRAM;
    uint8_t m_numROMBanks;
    
public:
    Cartridge() {};
    
    bool loadFromFile(std::string path);
    
    inline uint8_t getNumBanks()
    {
        return m_numROMBanks;
    }
    
    inline uint8_t readMemory(uint16_t addr)
    {
//        std::cout << "Memory read at " << std::hex << addr << " Value " << (int) m_PRG_ROM[addr] << std::endl;
        return m_PRG_ROM[addr];
    }
    inline void writeMemory(uint16_t addr, uint8_t value)
    {
        m_PRG_ROM[addr] = value;
//        std::cout << "Memory written at " << std::hex << addr << " Value " << (int) m_PRG_ROM[addr] << std::endl;
    }
    inline uint8_t PPUreadMemory(uint16_t addr)
    {
        return m_CHR_ROM[addr];
    }
    inline void PPUwriteMemory(uint16_t addr, uint8_t value)
    {
        m_CHR_ROM[addr] = value;
    }
    

    
};

#endif /* cartridge_hpp */
