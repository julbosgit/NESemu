//
//  main.cpp
//
//  Created 12/27/20.
//

#include <iostream>

#include "cpu.hpp"
#include "cartridge.hpp"
#include "nessystem.hpp"

int main(int argc, const char * argv[]) {
    

    Cartridge c;
    
//   c.loadFromFile("SMB.nes");
//   c.loadFromFile("DK.nes");
//    c.loadFromFile("PM.nes");
//    c.loadFromFile("BF.nes");
    
    NESsystem NES(&c);
    
    NES.go();
    
    return 0;
}
