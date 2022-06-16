//
//  Color.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 11/06/22.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Global.hpp"

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
//        # 'color_a' and 'color_b' are RGB tuples
//        # 't' is a value between 0.0 and 1.0
//        # this is a naive interpolation
//        return tuple(int(a + (b - a) * t) for a, b in zip(color_a, color_b))
    }
    static const Color Black;
    static const Color White;
};
#endif /* Color_hpp */
