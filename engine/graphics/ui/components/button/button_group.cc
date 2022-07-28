#include "button_group.h"

ButtonGroup::ButtonGroup(SDL_Rect rect){
    rect_ = rect;
    // int x = rect_.x, y = rect_.y;
    // std::stringstream ss;
    // ss << text;
    // std::string segment;
    // while(std::getline(ss, segment, ' ')){
    //     buttons_.push_back({{x,y,button_rect.w,button_rect.h},segment});
    //     x += button_rect.w;
    //     if(x >= rect_.w){
    //         x = rect_.x;
    //         y += button_rect.h;
    //     }
    // }
}

void ButtonGroup::AddButtons(std::vector<Button> buttons){
    for(int i=0;i<buttons.size();i++){
        buttons_.push_back(buttons[i]);
    }
}

ButtonGroup::~ButtonGroup(){}

SDL_Surface* ButtonGroup::GetUpdatedSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    for(int i=0;i<buttons_.size();i++){
        Button *button = &buttons_[i];
        SDL_BlitSurface(button->surface_, nullptr, surf, &button->rect_);
    }
    return surf;
}

void ButtonGroup::Click(){
    // if(!SDL_PointInRect(&click_position,&rect_))
    //     return;
    // click_position.x -= rect_.x;
    // click_position.y -= rect_.y;
    // for(int i=0;i<buttons_.size();i++){
    //     if(SDL_PointInRect(&click_position,&buttons_[i].rect_)){
    //         fn_(i);
    //     }
    // }
}

