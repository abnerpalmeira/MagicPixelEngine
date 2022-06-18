//
//  UI.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "UI.hpp"

UI::UI(SDL_Renderer *renderer, SDL_Rect rect, Color color){
    renderer_ = renderer;
    rect_ = rect;
    color_ = color;
    CreateTexture();
}

void UI::CreateTexture(){
    if(texture_ != NULL) delete texture_;
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0,rect_.w,rect_.h,32,kPixelFormat);
    SDL_FillRect(surf, NULL, color_.GetSDLMap());
    for(int i=0;i<button_group_.size();i++){
        SDL_Surface *temp_surf = button_group_[i].ToSurface();
        SDL_BlitSurface(temp_surf, NULL, surf, &button_group_[i].rect_);
        SDL_FreeSurface(temp_surf);
    }
    texture_ = new Texture(renderer_,rect_, surf);
    SDL_FreeSurface(surf);
}

UI::~UI(){
    delete texture_;
}

void UI::AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,const char *font_file){
    button_group_.push_back(ButtonGroup(group_rect,button_rect,text,font_file));
    CreateTexture();
}

//bool UI::IsButtonClicked(const SDL_Point *click_position, Uint8 &button) const{
//    for(int i = 0; i < button_count_; ++i){
//        if(SDL_PointInRect(click_position, &buttons_[i])){
//            _button = i;
//            return true;
//        }
//    }
//    return false;
//}

//void Texture::changeText(std::string _text){
//    SDL_Surface *surf = TTF_RenderText_Solid(font_, _text.c_str(), kTextColor);
//    SDL_Texture *tempTex = SDL_CreateTextureFromSurface(renderer_, surf);
//    SDL_FreeSurface(surf);
//    if(tempTex)
//    {
//        if(object_texture_) { SDL_DestroyTexture(object_texture_); }
//        object_texture_ = tempTex;
//        SDL_QueryTexture(object_texture_, nullptr, nullptr, &rect_->w, &rect_->h);
//    }
//}
