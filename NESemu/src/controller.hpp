//
//  controller.hpp
//
//  Created 1/2/21.
//

#ifndef controller_hpp
#define controller_hpp

#include <bitset>
#include <SDL.h>

enum ControllerButtons {
    A=0,
    B,
    Select,
    Start,
    Up,
    Down,
    Left,
    Right
};

class Controller {

public:
    Controller() : _inputPos{0}, _inputs{0}, _strobe{false}
    {}
    uint8_t getNextInput();
    void setStrobe(bool);
    void recordKey(SDL_Event);
    
private:
    uint8_t _inputPos;
    std::bitset<8> _inputs;
    bool _strobe;
    
    
};

#endif /* controller_hpp */
