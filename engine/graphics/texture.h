//
//  texture.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 07/06/22.
//

#pragma once

#include <SDL.h>
#include "core/global.h"
#include "core/renderer.h"

class Texture{
public:
    Texture();
    Texture(SDL_Rect rect,float scale = 1);
    Texture(SDL_Rect rect, SDL_Surface *surface, float scale = 1);
    Texture(const char *file, float scale = 1);
    ~Texture();
    void UpdateTexture(const void *pixels);
    void SetTextureBlendMode(SDL_BlendMode blend_mode);
    void SetTextureAlphaMod(Uint8 alpha);
    void Render();
    float GetScale();
    SDL_Rect rect_;
    SDL_Texture *texture_;
    float scale_;
protected:
};
