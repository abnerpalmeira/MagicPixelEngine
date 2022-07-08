//
//  color.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 11/06/22.
//

#pragma once

#include <stdio.h>
#include <SDL.h>
#include "core/global.h"

class Color{
    bool changed_;
   
    int r_,g_,b_,a_;
public:
    Uint32 pixel_value_;
    Color();
    Color(int r,int g,int b,int a);
    Uint32 GetSDLMap();
    static Color Interpolate(Color x, Color y, float t){
        int r = (int)(x.r_ + (y.r_ - x.r_)*t);
        int g = (int)(x.g_ + (y.g_ - x.g_)*t);
        int b = (int)(x.b_ + (y.b_ - x.b_)*t);
        int a = (int)(x.a_ + (y.a_ - x.a_)*t);
        return Color(r,g,b,a);
    }
    static const Color Black;
    static const Color White;
};
