//
//  text.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#pragma once

#include <stdio.h>
#include <string>
#include "SDL2/SDL.h"
#include "global.hpp"

class Text{
public:
    Text(SDL_Rect rect, std::string text);
    SDL_Surface* ToSurface();
    std::string text_;
    SDL_Rect rect_;
};

#endif /* Text_hpp */
