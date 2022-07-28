#include<SDL.h>
#pragma once

class UIComponent{
public:
    UIComponent() = default;
    virtual ~UIComponent(){
        SDL_FreeSurface(surface_);
    }
    virtual SDL_Surface* GetUpdatedSurface(){ return nullptr; }
    virtual void OnClick(){}
    virtual void OnHover(){}
    virtual void Update(){}
    SDL_Surface *surface_ = nullptr;
    SDL_Rect rect_;
protected:
private:
};