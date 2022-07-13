//
//  input_manager.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#pragma once

#include <map>
#include <SDL.h>
#include "common/geometry/vector.h"

enum class KeyState{
    UP,
    DOWN, 
    JUSTUP,
    JUSTDOWN,
    DOWNREPEAT
};
class InputManager{
public:

    static InputManager* Instance(){
        if(!ptr_instance_)
            ptr_instance_ = new InputManager;
        return ptr_instance_;
    }
    bool GetKey(SDL_Keycode key, KeyState state);
    bool GetButton(Uint8 button, KeyState state);
    void PreUpdate();
    void Handle(const SDL_Event &event);
    std::map<SDL_Keycode, KeyState> key_states_;
    std::map<Uint8, KeyState> mouse_states_;
    SDL_Point mouse_position_;
    Sint32 mouse_wheel_;
private:
    InputManager() = default;
    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);
    ~InputManager();
    static InputManager* ptr_instance_;
};
