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

UI::~UI(){
    delete texture_;
}

void UI::UpdateTexture(){
    if(texture_ != nullptr) delete texture_;
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0,rect_.w,rect_.h,32,kPixelFormat);
    SDL_FillRect(surf, NULL, background_color_.GetSDLMap());
    for(auto component: ui_components_){
        int x = SDL_BlitSurface(component->surface_, NULL, surf, &component->rect_);
    }
    texture_ = new Texture(rect_, surf);
    SDL_FreeSurface(surf);
}

void UI::AddComponent(UIComponent *ui_component){
    ui_components_.push_back(ui_component);
}

void UI::Update(){
}

void UI::Render(){
    texture_->Render();
}