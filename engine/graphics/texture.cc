//
//  texture.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 01/06/22.
//

#include "texture.h"

Texture::Texture(){
}

Texture::Texture(float scale, SDL_Rect rect){
    rect_ = rect;
    scale_ = scale;
    texture_ = SDL_CreateTexture(Renderer::Instance()->renderer_, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
}

Texture::Texture(float scale, const char *file){
    // SDL_Surface* surface = IMG_Load(file);
    // texture_= SDL_CreateTextureFromSurface(renderer, surface);
    // scale_ = scale;
    // SDL_FreeSurface(surface);
}

Texture::Texture(float scale, SDL_Rect rect, SDL_Surface *surface){
    rect_ = rect;
    scale_ = scale;
    texture_= SDL_CreateTextureFromSurface(Renderer::Instance()->renderer_, surface);
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
        SDL_RenderCopyF(Renderer::Instance()->renderer_, texture_, nullptr, &temp);
    }
    else SDL_RenderCopy(Renderer::Instance()->renderer_, texture_, nullptr, &rect_);
}

float Texture::GetScale(){
    return scale_;
}
