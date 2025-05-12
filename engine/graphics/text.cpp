//
//  text.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#pragma once

#include <stdio.h>
#include <string>
#include <SDL.h>
#include "core/global.h"

class Text{
public:
    Text(SDL_Rect rect, std::string text);
    SDL_Surface* ToSurface();
    std::string text_;
    SDL_Rect rect_;
};
