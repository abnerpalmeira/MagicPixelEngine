#include <SDL.h>
#include "core/global.h"

#pragma once

class Window{
public:
    static Window* Instance(){
        if(!ptr_instance_){
            ptr_instance_ = new Window;
            ptr_instance_->window_ = SDL_CreateWindow("Magic Pixel Engine",0,0,kScreenWidth, kScreenHeight,SDL_WINDOW_MAXIMIZED);
        }
        return ptr_instance_;
    }
    SDL_Window *window_;
private:
    Window() = default;
    Window(const Window&);
    Window& operator=(const Window&);
    ~Window();
    static Window* ptr_instance_;
};