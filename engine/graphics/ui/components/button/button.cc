//
//  button.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "button.h"

Button::Button(){
    
}

Button::Button(SDL_Rect rect,Color background_color, std::function<void()> fn){
    rect_ = rect;
    background_color_ = background_color;
    fn_ = fn;
    surface_ = GetUpdatedSurface();
}

Button::~Button(){
    
}

SDL_Surface* Button::GetUpdatedSurface(){
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0,rect_.w,rect_.h,32,kPixelFormat);
    SDL_FillRect(surf, NULL, background_color_.GetSDLMap());
    return surf;
}

void Button::OnClick(){
    fn_();
}

void Button::OnHover(){

}
