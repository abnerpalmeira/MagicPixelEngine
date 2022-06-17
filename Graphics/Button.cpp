//
//  Button.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "Button.hpp"

ButtonGroup::ButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text, TTF_Font *font){
    font_ = font;
    std::stringstream ss;
    ss << text;
    rect_ = group_rect;
    int x = group_rect.x, y = group_rect.y;
    std::string segment;
    while(std::getline(ss, segment, ' ')){
        SDL_Rect button_rect;
        buttons_.push_back({{x,y,button_rect.w,button_rect.h},segment});
        x += button_rect.w;
        if(x >= x+group_rect.w){
            x = group_rect.x;
            y += button_rect.h;
        }
    }
}

SDL_Surface* ButtonGroup::ToSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    for(int i=0;i<buttons_.size();i++){
        SDL_Surface *temp_surf = TTF_RenderText_Solid(font_, buttons_[i].text_.c_str(), kTextColor);
        int text_width;
//        TTF_SizeText(font_, buttons_[i].text_.c_str(), &text_width, nullptr);
//        SDL_Rect temp_rect = {buttons_[i].x - rect_->x + buttonWidth / 2 - textWidth / 2), buttons_[i].y - rect_->y, 0, 0};
        SDL_BlitSurface(temp_surf, nullptr, surf, &buttons_[i].rect_);
        SDL_FreeSurface(temp_surf);
    }
    return surf;
}


