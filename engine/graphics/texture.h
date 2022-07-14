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
    Texture(float scale, SDL_Rect rect);
    Texture(float scale, SDL_Rect rect, SDL_Surface *surface);
    Texture(float scale, const char *file);
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
