//
//  button.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "button.h"

ButtonGroup::ButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,std::function<void(int)> fn){
    fn_ = fn;
    rect_ = group_rect;
    int x = rect_.x, y = rect_.y;
    std::stringstream ss;
    ss << text;
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

ButtonGroup::~ButtonGroup(){
//    TTF_CloseFont(font_);
}

SDL_Surface* ButtonGroup::ToSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    for(int i=0;i<buttons_.size();i++){
        SDL_Surface *temp_surf = TTF_RenderText_Solid(font, buttons_[i].text_.c_str(), kTextColor);
        int x = buttons_[i].rect_.x + ((buttons_[i].rect_.w + temp_surf->w)/2 - temp_surf->w);
        int y = buttons_[i].rect_.y + ((buttons_[i].rect_.h + temp_surf->h)/2 - temp_surf->h);
        SDL_Rect temp_rect = {x,y,temp_surf->w,temp_surf->h};
        SDL_BlitSurface(temp_surf, nullptr, surf, &temp_rect);
        SDL_FreeSurface(temp_surf);
    }
    return surf;
}

void ButtonGroup::Click(SDL_Point click_position){
    if(!SDL_PointInRect(&click_position,&rect_))
        return;
    click_position.x -= rect_.x;
    click_position.y -= rect_.y;
    for(int i=0;i<buttons_.size();i++){
        if(SDL_PointInRect(&click_position,&buttons_[i].rect_)){
            fn_(i);
        }
    }
}


