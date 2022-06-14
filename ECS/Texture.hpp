//
//  Texture.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 07/06/22.
//

#ifndef Texture_hpp
#define Texture_hpp
#pragma once
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Game.hpp"
#include "Global.hpp"
 
class Texture{
    
public:
    static SDL_Texture* LoadTexture(const char* file);
    static SDL_Texture* LoadTexture(SDL_Renderer *renderer,SDL_Rect rect);
    static SDL_Texture* LoadTexture(SDL_Renderer *renderer, SDL_Rect rect, TTF_Font *_font, std::string _text);
    
};

#endif /* Texture_hpp */
