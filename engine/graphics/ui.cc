//
//  UI.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "graphics/ui.h"

UI::UI(SDL_Rect rect, Color color){
    rect_ = rect;
    color_ = color;
    CreateTexture();
}

void UI::CreateTexture(){
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0,rect_.w,rect_.h,32,kPixelFormat);
    SDL_FillRect(surf, NULL, color_.GetSDLMap());
    for(int i=0;i<button_group_.size();i++){
        SDL_Surface *temp_surf = button_group_[i].ToSurface();
        SDL_BlitSurface(temp_surf, NULL, surf, &button_group_[i].rect_);
        SDL_FreeSurface(temp_surf);
    }
    for(int i=0;i<text_.size();i++){
        SDL_Surface *temp_surf = text_[i].ToSurface();
        SDL_BlitSurface(temp_surf, NULL, surf, &text_[i].rect_);
        SDL_FreeSurface(temp_surf);
        
    }
    texture_ = Texture(1,rect_, surf);
    SDL_FreeSurface(surf);
}

void UI::AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,std::function<void(int)> fn){
    button_group_.push_back(ButtonGroup(group_rect,button_rect,text,fn));
    CreateTexture();
}

void UI::AddText(SDL_Rect text_rect, std::string text){
    text_.push_back(Text(text_rect,text));
    CreateTexture();
}

bool UI::IsClicked(){
    return false;
}

void UI::Click(){
    SDL_Point click_position = cursor;
    click_position.x -= rect_.x;
    click_position.y -= rect_.y;
    for(int i=0;i<button_group_.size();i++){
        button_group_[i].Click(click_position);
    }
}

void UI::Update(){
}

void UI::Render(){
}