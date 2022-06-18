//
//  Button.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "Button.hpp"

ButtonGroup::ButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text, const char *font_file){
    TTF_Init();
    font_ = TTF_OpenFont(font_file, 16);
    std::stringstream ss;
    ss << text;
    rect_ = group_rect;
    int x = rect_.x, y = rect_.y;
    std::string segment;
    while(std::getline(ss, segment, ' ')){
        buttons_.push_back({{x,y,button_rect.w,button_rect.h},segment});
        x += button_rect.w;
        if(x >= rect_.w){
            x = rect_.x;
            y += button_rect.h;
        }
    }
}

SDL_Surface* ButtonGroup::ToSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    for(int i=0;i<buttons_.size();i++){
        SDL_Surface *temp_surf = TTF_RenderText_Solid(font_, buttons_[i].text_.c_str(), kTextColor);
        int x = buttons_[i].rect_.x + ((buttons_[i].rect_.w + temp_surf->w)/2 - temp_surf->w);
        int y = buttons_[i].rect_.y + ((buttons_[i].rect_.h + temp_surf->h)/2 - temp_surf->h);
        SDL_Rect temp_rect = {x,y,temp_surf->w,temp_surf->h};
        SDL_BlitSurface(temp_surf, nullptr, surf, &temp_rect);
        SDL_FreeSurface(temp_surf);
    }
    return surf;
}


