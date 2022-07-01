//
//  InputManager.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "InputManager.hpp"

InputManager* InputManager::ptr_instance_ = nullptr;

void InputManager::PreUpdate(){
    for(auto& [key_index, state] : key_states_){
        if(state == KeyState::JUSTUP){
            state = KeyState::UP;
        }else if(state == KeyState::JUSTDOWN){
            state = KeyState::DOWN;
        }
    }
}

void InputManager::Handle(const SDL_Event* event){
    switch (event->type) {
        case SDL_KEYDOWN:
            key_states_[event->key.keysym.sym] = KeyState::JUSTDOWN;
            break;
        case SDL_KEYUP:
            key_states_[event->key.keysym.sym] = KeyState::JUSTUP;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse_states_[event->button.button] = KeyState::DOWN;
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_states_[event->button.button] = KeyState::UP;
            break;
        default:
            break;
    }
}
