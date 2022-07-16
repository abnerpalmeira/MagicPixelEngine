#include<SDL.h>
#pragma once

class UIComponent{
public:
    UIComponent() = default;
    virtual ~UIComponent(){
        SDL_FreeSurface(surface_);
    }
    virtual SDL_Surface* Surface(){}
    virtual void OnClick(){}
    virtual void OnHover(){}
    virtual void Update(){}
protected:
    SDL_Rect rect_;
    SDL_Surface *surface_ = nullptr;
private:
};