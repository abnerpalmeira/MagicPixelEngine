//
//  UI.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "ui.h"

UI::UI(SDL_Rect rect, Color background_color){
    rect_ = rect;
    background_color_ = background_color;
    UpdateTexture();
}

void UI::UpdateTexture(){
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0,rect_.w,rect_.h,32,kPixelFormat);
    SDL_FillRect(surf, NULL, background_color_.GetSDLMap());
    for(int i=0;i<ui_components_.size();i++){
        SDL_Surface *temp_surf = ui_components_[i].Surface();
        SDL_BlitSurface(temp_surf, NULL, surf, &ui_components_[i].rect_);
        SDL_FreeSurface(temp_surf);
    }
    texture_ = Texture(rect_, surf);
    SDL_FreeSurface(surf);
}

void UI::AddComponent(UIComponent &ui_component){
    ui_components_.push_back(ui_component);
}

// void UI::AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,std::function<void(int)> fn){
//     button_group_.push_back(ButtonGroup(group_rect,button_rect,text,fn));
//     UpdateTexture();
// }

// void UI::AddText(SDL_Rect text_rect, std::string text){
//     text_.push_back(Text(text_rect,text));
//     UpdateTexture();
// }

void UI::Update(){
}

void UI::Render(){
}