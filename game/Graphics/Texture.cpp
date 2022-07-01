//
//  Texture.cpp
//  MagicPixel
//
//  Created by Abner Palmeira on 01/06/22.
//

#include "Texture.hpp"

Texture::Texture(SDL_Renderer *renderer, float scale, SDL_Rect rect){
    rect_ = rect;
    scale_ = scale;
    renderer_ = renderer;
    texture_ = SDL_CreateTexture(renderer, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
}

Texture::Texture(SDL_Renderer *renderer, float scale, const char *file){
    SDL_Surface* surface = IMG_Load(file);
    texture_= SDL_CreateTextureFromSurface(renderer, surface);
    scale_ = scale;
    SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Renderer *renderer, SDL_Rect rect, SDL_Surface *surface){
    rect_ = rect;
    scale_ = 1;
    renderer_ = renderer;
    texture_= SDL_CreateTextureFromSurface(renderer, surface);
}

Texture::~Texture(){
    SDL_DestroyTexture(texture_);
}

void Texture::UpdateTexture(const void *pixels){
    SDL_UpdateTexture(texture_, nullptr, pixels, (rect_.w) * sizeof(Uint32));
}

void Texture::SetTextureBlendMode(SDL_BlendMode blend_mode){
    SDL_SetTextureBlendMode(texture_, blend_mode);
}

void Texture::SetTextureAlphaMod(Uint8 alpha){
    SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::Render(){
    if(scale_ != 1){
        SDL_FRect temp = {(float)rect_.x,(float)rect_.y,scale_*rect_.w,scale_*rect_.h};
        SDL_RenderCopyF(renderer_, texture_, nullptr, &temp);
    }
    else SDL_RenderCopy(renderer_, texture_, nullptr, &rect_);
}

float Texture::GetScale(){
    return scale_;
}
