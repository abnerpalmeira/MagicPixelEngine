//
//  Rectangle.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include "SDL2/SDL.h"

class Rectangle{
public:
    Rectangle(int x,int y,int w,int h);
    bool PointInRect(const SDL_Point *click_position);
    int x_;
    int y_;
    int w_;
    int h_;
    SDL_Rect sdl_rect_;
};

#endif /* Rectangle_hpp */
