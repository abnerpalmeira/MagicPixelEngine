#include <SDL.h>
#include "core/window.h"

#pragma once

class Renderer{
public:
    static Renderer* Instance(){
        if(!ptr_instance_){
            ptr_instance_ = new Renderer;
            ptr_instance_->renderer_ = SDL_CreateRenderer(Window::Instance()->window_, -1,SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawBlendMode(ptr_instance_->renderer_, SDL_BLENDMODE_BLEND);
        }
        return ptr_instance_;
    }
    SDL_Renderer *renderer_;
private:
    Renderer() = default;
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
    ~Renderer();
    static Renderer* ptr_instance_;
};