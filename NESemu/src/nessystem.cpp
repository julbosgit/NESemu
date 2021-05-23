//
//  nessystem.cpp
//
//  Created 1/1/21.
//

#include <SDL.h>
#include <chrono>
#include "nessystem.hpp"


void NESsystem::go()
{
    
//    _ppu->_displayPatternTables();
    _ppu->initGameWindow();
//    _ppu->_displayPatternTables();
    
    uint32_t oldCyc=0, newCyc=0;
    
    auto start = std::chrono::high_resolution_clock::now();
    int ppu_cnt = 0;
    for(;;) {
        newCyc = _cpu->CPU_cycle();
        
        for(int i=0 ; i < (newCyc-oldCyc) ; i++) {
            _ppu->PPU_step();
            _ppu->PPU_step();
            _ppu->PPU_step();
            ppu_cnt+=3;
        }
        oldCyc = newCyc;
        
        auto stop = std::chrono::high_resolution_clock::now();
        
        // update each frame (60 fps)
        if(ppu_cnt >= 341*262) {
            auto dur_millis = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

            while(dur_millis < std::chrono::milliseconds(10)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                stop = std::chrono::high_resolution_clock::now();
                dur_millis = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
            }
//            oldCyc = newCyc;
            ppu_cnt = 0;
         
            if(handleEvents())
                break;
            start = std::chrono::high_resolution_clock::now();
        }
    }
}


bool NESsystem::handleEvents()
{
    SDL_Event e;
    
    SDL_PollEvent(&e);
      
    switch( e.type ){
          /* Keyboard event */
          /* Pass the event data onto PrintKeyInfo() */
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            _ctrl->recordKey(e);
            break;
        
        case SDL_QUIT:
            return true;
            
        default: break;
    }
          
    return false;
      
}
