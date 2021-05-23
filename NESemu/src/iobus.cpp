//
//  iobus.cpp
//
//  Created 12/30/20.
//

#include "iobus.hpp"

uint8_t IOBus::readMemory(uint16_t addr)
{
    if(addr <= UPPER_RAM_ADDR) {
        // RAM is mirrored 4 times
        return _RAM[addr % 0x800];
    }
    if((addr <= UPPER_PPU_ADDR) || (addr == 0x4014) || (addr == JOY1) || (addr == JOY2)) {
        if(addr <= UPPER_PPU_ADDR) {
        // PPU IO registers are mirrored every 8 bytes in $2008-$3FFF
            addr = addr & 0x2007;
        }
        auto it = m_readCallbacks.find(static_cast<IORegisters>(addr));
        if (it != m_readCallbacks.end())
            return (it -> second)();
        else {
            std::cout << "No read callback registered for I/O register at: " << std::hex << +addr << std::endl;
            return 0;
        }
    }

    if(addr >= LOWER_BANK_ROM)
    {
        if(c->getNumBanks() == 1)
            return c->readMemory(addr-UPPER_BANK_ROM);
        if(c->getNumBanks() == 2)
            return c->readMemory(addr-LOWER_BANK_ROM);
    }
  //  std::cout << "Address read not supported" << std::endl;
    return 0;
}

void IOBus::writeMemory(uint16_t addr, uint8_t value)
   {
       if(addr <= UPPER_RAM_ADDR) {
           _RAM[addr] = value;
       }
       else if((addr <= UPPER_PPU_ADDR) || (addr == 0x4014) || (addr == JOY1) || (addr == JOY2)) {
           if(addr <= UPPER_PPU_ADDR) {
           // PPU IO registers are mirrored every 8 bytes in $2008-$3FFF
               addr = addr & 0x2007;
           }
               
           auto it = m_writeCallbacks.find(static_cast<IORegisters>(addr));
           if (it != m_writeCallbacks.end())
               (it -> second)(value);
           else
               std::cout << "No write callback registered for I/O register at: " << std::hex << addr << std::endl;
       }
       else if(addr > LOWER_BANK_ROM)
       {
           if(c->getNumBanks() == 1)
               c->writeMemory(addr-UPPER_BANK_ROM, value);
           else if(c->getNumBanks() == 2)
                c->writeMemory(addr-LOWER_BANK_ROM, value);
           else std::cout << "Number of banks not supported" << std::endl;
       }
       else
           std::cout << "Address write not supported @ " << std::hex << addr << std::endl;
   }


bool IOBus::setWriteCallback(IORegisters reg, std::function<void(uint8_t)> callback)
{
    if (!callback)
    {
        std::cout << "callback argument is nullptr" << std::endl;
        return false;
    }
    return m_writeCallbacks.emplace(reg, callback).second;
}

bool IOBus::setReadCallback(IORegisters reg, std::function<uint8_t(void)> callback)
{
    if (!callback)
    {
        std::cout << "callback argument is nullptr" << std::endl;
        return false;
    }
    return m_readCallbacks.emplace(reg, callback).second;
}

bool IOBus::setNMICallback(std::function<bool(void)> callback)
{
    if (!callback)
    {
        std::cout << "callback argument is nullptr" << std::endl;
        return false;
    }
    m_NMICallback = callback;
    return true;
}


bool IOBus::setDMACPUCallback(std::function<void(void)> callback)
{
    if (!callback)
    {
        std::cout << "callback argument is nullptr" << std::endl;
        return false;
    }
    m_DMACPUCallback = callback;
    return true;
}
