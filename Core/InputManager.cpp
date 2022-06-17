//
//  InputManager.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "InputManager.hpp"

void InputManager::PreUpdate(){
    for(auto& [key_index, state] : key_states_){
        state = (state == KeyState::JUSTUP)? KeyState::UP : KeyState::DOWN;
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
