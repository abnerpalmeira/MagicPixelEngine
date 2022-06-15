//
//  Texture.cpp
//  MagicPixel
//
//  Created by Abner Palmeira on 01/06/22.
//

#include "Texture.hpp"

SDL_Texture* Texture::LoadTexture(const char *file){
    SDL_Surface* surface = IMG_Load(file);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer_, surface);
    SDL_free(surface);
    
    return texture;
}

SDL_Texture* Texture::LoadTexture(SDL_Renderer *renderer,SDL_Rect rect){
    return SDL_CreateTexture(renderer, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
}

