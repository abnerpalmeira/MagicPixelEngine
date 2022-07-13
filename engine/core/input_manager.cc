//
//  input_manager.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "input_manager.h"

InputManager* InputManager::ptr_instance_ = nullptr;

void InputManager::PreUpdate(){
    mouse_wheel_ = 0;
    for(auto& [key_index, state] : key_states_){
        if(state == KeyState::JUSTUP){
            state = KeyState::UP;
        }else if(state == KeyState::JUSTDOWN){
            state = KeyState::DOWN;
        }
    }
}

void InputManager::Handle(const SDL_Event &event){
    switch (event.type) {
        case SDL_KEYDOWN:
            if(key_states_[event.key.keysym.sym] != KeyState::DOWN)
                key_states_[event.key.keysym.sym] = KeyState::JUSTDOWN;
            break;
        case SDL_KEYUP:
            key_states_[event.key.keysym.sym] = KeyState::JUSTUP;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse_states_[event.button.button] = KeyState::DOWN;
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_states_[event.button.button] = KeyState::UP;
            break;
        case SDL_MOUSEMOTION:
            mouse_position_.x = event.button.x;
            mouse_position_.y = event.button.y;
        case SDL_MOUSEWHEEL:
            mouse_wheel_ + event.wheel.y;
        default:
            break;
    }
}

bool InputManager::GetKey(SDL_Keycode key, KeyState state){
    return  key_states_[key] == state;
}

bool InputManager::GetButton(Uint8 button, KeyState state){
    return  mouse_states_[button] == state;
}