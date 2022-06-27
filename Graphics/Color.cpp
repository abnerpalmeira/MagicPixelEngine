//
//  Color.cpp
//  2D Sand
//
//  Created by Abner Palmeira on 11/06/22.
//

#include "Color.hpp"

Color::Color(){
    r_ = 0;
    b_ = 0;
    g_ = 0;
    a_ = 0;
    pixel_value_ = 0;
    changed_ = true;
}

Color::Color(int r,int g,int b,int a){
    r_ = r;
    b_ = b;
    g_ = g;
    a_ = a;
    changed_ = true;
}

Uint32 Color::GetSDLMap(){
    if(changed_){
        changed_ = false;
        pixel_value_ = SDL_MapRGBA(pixel_format, r_, g_, b_, a_);
    }
    return pixel_value_;
}

const Color Color::Black(0, 0, 0,255);
const Color Color::White(255, 255, 255,255);
