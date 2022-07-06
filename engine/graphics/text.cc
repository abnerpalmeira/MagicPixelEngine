//
//  text.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#include "text.h"

Text::Text(SDL_Rect rect, std::string text){
    rect_ = rect;
    text_ = text;
}

SDL_Surface* Text::ToSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    SDL_Surface *temp_surf = TTF_RenderText_Solid(font, text_.c_str(), kTextColor);
    int x = rect_.x + ((rect_.w + temp_surf->w)/2 - temp_surf->w);
    int y = rect_.y + ((rect_.h + temp_surf->h)/2 - temp_surf->h);
    SDL_Rect temp_rect = {x,y,temp_surf->w,temp_surf->h};
    SDL_BlitSurface(temp_surf, nullptr, surf, &temp_rect);
    SDL_FreeSurface(temp_surf);
    return surf;
}
