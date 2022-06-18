//
//  Texture.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 07/06/22.
//

#ifndef Texture_hpp
#define Texture_hpp
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Global.hpp"

class Texture{
public:
    Texture(SDL_Renderer *renderer, float scale, SDL_Rect rect);
    Texture(SDL_Renderer *renderer, SDL_Rect rect, SDL_Surface *surface);
    Texture(SDL_Renderer *renderer, float scale, const char *file);
    ~Texture();
    void UpdateTexture(const void *pixels);
    void SetTextureBlendMode(SDL_BlendMode blend_mode);
    void SetTextureAlphaMod(Uint8 alpha);
    void Render();
    float GetScale();
    SDL_Rect rect_;
protected:
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
private:
    float scale_;
};

#endif /* Texture_hpp */
