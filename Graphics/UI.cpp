//
//  UI.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "UI.hpp"

UI::UI(SDL_Renderer *renderer, float scale, SDL_Rect rect, const char *font_file) : Texture(renderer,scale,rect){
    TTF_Init();
    font_ = TTF_OpenFont(font_file, 16);
}

void UI::AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text){
    button_group_.push_back(ButtonGroup(group_rect,button_rect,text,font_));
    SDL_Surface *surf = button_group_.back().ToSurface();
    texture_ = SDL_CreateTextureFromSurface(renderer_, surf);
    SDL_FreeSurface(surf);
    SDL_QueryTexture(texture_, nullptr, nullptr, &rect_.w, &rect_.h);
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
