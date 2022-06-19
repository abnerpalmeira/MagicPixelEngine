//
//  InputManager.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <stdio.h>
#include <map>
#include "SDL2/SDL.h"

class InputManager{
public:
    enum class KeyState{
        UP,
        DOWN, 
        JUSTUP,
        JUSTDOWN,
        DOWNREPEAT
      };
    std::map<SDL_Keycode, KeyState> key_states_;
    std::map<Uint8, KeyState> mouse_states_;
    void PreUpdate();
    void Handle(const SDL_Event* event);
private:
};
#endif /* InputManager_hpp */
