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
    static InputManager* Instance(){
        if(!ptr_instance_)
            ptr_instance_ = new InputManager;
        return ptr_instance_;
    }
    void PreUpdate();
    void Handle(const SDL_Event* event);
    std::map<SDL_Keycode, KeyState> key_states_;
    std::map<Uint8, KeyState> mouse_states_;
private:
    InputManager() = default;
    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);
    ~InputManager();
    static InputManager* ptr_instance_;
};

#endif /* InputManager_hpp */
