//
//  nessystem.hpp
//
//  Created 1/1/21.
//

#ifndef nessystem_hpp
#define nessystem_hpp

#include <chrono>
#include <thread>

#include "cpu.hpp"
#include "ppu.hpp"
#include "iobus.hpp"
#include "cartridge.hpp"
#include "controller.hpp"


class NESsystem {
    
public:
    NESsystem(Cartridge *c) {
        _iob = std::make_shared<IOBus>(c);
        _cpu = std::make_unique<CPU>(_iob);
        _ppu = std::make_unique<PPU>(_iob);
        _ctrl = std::make_unique<Controller>();
        _ctrl2 = std::make_unique<Controller>();
        
        if(!_iob->setReadCallback(PPUSTATUS, [&](void) {return _ppu->getStatus();}) ||
            !_iob->setReadCallback(PPUDATA, [&](void) {return _ppu->getData();}) ||
            !_iob->setReadCallback(JOY1, [&](void) {return _ctrl->getNextInput();}) ||
            !_iob->setReadCallback(JOY2, [&](void) {return _ctrl2->getNextInput();}) ||
            !_iob->setReadCallback(OAMDATA, [&](void) {return _ppu->getOAMData();}))
        {
            std::cout << "Critical error: Failed to set I/O callbacks" << std::endl;
        }

        if(!_iob->setNMICallback([&](void){ return _ppu->getNMI();}))
            std::cout << "Critical error: Failed to set NMI callback" << std::endl;
        
        if(!_iob->setDMACPUCallback([&](void){ _cpu->ProcessDMAcycles();}))
            std::cout << "Critical error: Failed to set DMA cycles callback" << std::endl;

        if(!_iob->setWriteCallback(PPUCTRL, [&](uint8_t b) {_ppu->control(b);}) ||
            !_iob->setWriteCallback(PPUMASK, [&](uint8_t b) {_ppu->setMask(b);}) ||
            !_iob->setWriteCallback(OAMADDR, [&](uint8_t b) {_ppu->setOAMAddress(b);}) ||
            !_iob->setWriteCallback(PPUADDR, [&](uint8_t b) {_ppu->setDataAddress(b);}) ||
            !_iob->setWriteCallback(PPUSCROL, [&](uint8_t b) {_ppu->setScroll(b);}) ||
            !_iob->setWriteCallback(PPUDATA, [&](uint8_t b) {_ppu->setData(b);}) ||
            !_iob->setWriteCallback(OAMDMA, [&](uint8_t b) {_ppu->DMA(b);}) ||
            !_iob->setWriteCallback(JOY1, [&](uint8_t b) {_ctrl->setStrobe(b & 0x01);}) ||
           !_iob->setWriteCallback(JOY2, [&](uint8_t b) {_ctrl2->setStrobe(b & 0x01);}) ||
            !_iob->setWriteCallback(OAMDATA, [&](uint8_t b) {_ppu->setOAMData(b);}))
        {
            std::cout << "Critical error: Failed to set I/O callbacks" << std::endl;
        }
        
    }
    
    void go();
    
private:
    std::shared_ptr<IOBus> _iob;
    std::unique_ptr<CPU> _cpu;
    std::unique_ptr<PPU> _ppu;
    std::unique_ptr<Controller> _ctrl, _ctrl2;
    
    bool handleEvents();
};

#endif /* nessystem_hpp */
