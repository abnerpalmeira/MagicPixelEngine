//
//  Rectangle.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#include "Rectangle.hpp"

Rectangle::Rectangle(int x,int y,int w,int h){
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    sdl_rect_ = {x_,y_,w_,h_};
}

bool Rectangle::PointInRect(const SDL_Point *click_position){
    return SDL_PointInRect(click_position, &sdl_rect_);
}
