//
//  controller.cpp
//
//  Created 1/2/21.
//

#include "controller.hpp"



uint8_t Controller::getNextInput()
{
    if(_inputPos > 7)
        _inputPos = 0;
    
    if(_strobe)
        _inputPos = 0;
    
    return _inputs.test(_inputPos++);
}


void Controller::setStrobe(bool s)
{
    _strobe = s;
}

void Controller::recordKey(SDL_Event event)
{
    ControllerButtons key;
    switch(event.key.keysym.sym)
    {
        case SDLK_UP: key = Up; break;
        case SDLK_DOWN: key = Down; break;
        case SDLK_LEFT: key = Left; break;
        case SDLK_RIGHT: key = Right; break;
        case SDLK_q: key = Start; break;
        case SDLK_w: key = Select; break;
        case SDLK_a: key = A; break;
        case SDLK_s: key = B; break;
        default: return;
    }
    
    if(event.type == SDL_KEYDOWN) {
        _inputs.set(key);
    }
    else if(event.type == SDL_KEYUP) {
        _inputs.reset(key);
    }
}
