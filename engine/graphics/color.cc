//
//  color.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 11/06/22.
//

#include "graphics/color.h"

Color::Color(){
    r_ = 0;
    b_ = 0;
    g_ = 0;
    a_ = 0;
    pixel_value_ = SDL_MapRGBA(pixel_format, r_, g_, b_, a_);
}

Color::Color(int r,int g,int b,int a){
    r_ = r;
    g_ = g;
    b_ = b;
    a_ = a;
    pixel_value_ = SDL_MapRGBA(pixel_format, r_, g_, b_, a_);
}

Uint32 Color::GetSDLMap(){
    return pixel_value_;
}

SDL_Color Color::GetSDLColor(){
    return {r_,g_,b_,a_};
}

const Color Color::Black(0, 0, 0,255);
const Color Color::White(255, 255, 255,255);
