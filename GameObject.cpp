//
//  GameObject.cpp
//  MagicPixel
//
//  Created by Abner Palmeira on 01/06/22.
//

#include "GameObject.hpp"

GameObject::GameObject(){
//    object_texture_ = Texture::LoadTexture(file);
}

void GameObject::Update(){
}
void GameObject::Render(){
    if(scale_ != 0){
        SDL_FRect temp;
        temp.w = scale_*rect_->w;
        temp.h = scale_*rect_->h;
        SDL_RenderCopyF(renderer_, object_texture_, nullptr, &temp);
    }
    else SDL_RenderCopy(renderer_, object_texture_, nullptr, rect_);
}

bool GameObject::isButtonClicked(const SDL_Point *_pos, Uint8 &_button) const
{
    for(int i = 0; i < button_count_; ++i)
    {
        if(SDL_PointInRect(_pos, &buttons_[i]))
        {
            _button = i;
            return true;
        }
    }
    return false;
}

void GameObject::InitializeTextureFromText(){
    
    button_count_ = 0;
    for(int i = 0; i < text_->size(); ++i) { if((*text_)[i] == ' ') { ++button_count_; } }
    buttons_ = new SDL_Rect[button_count_];

    int textHeight;
    TTF_SizeText(font_, "A", nullptr, &textHeight);
    Uint32 buttonHSpace = rect_->w;
    Uint32 buttonHMargin = buttonHSpace * kButtonMargin;
    Uint32 buttonVSpace = textHeight * (button_count_ / kButtonsInRow);
    Uint32 buttonVMargin = buttonVSpace * kButtonMargin;
    Uint32 buttonWidth = (buttonHSpace - buttonHMargin * (kButtonsInRow - 1)) / kButtonsInRow;
    Uint32 buttonHeight = (buttonVSpace - buttonVMargin * ((button_count_ / kButtonsInRow) - 1)) / std::max(button_count_ / kButtonsInRow, 1);
    for(int i = 0; i < button_count_; ++i)
    {
        buttons_[i].x = rect_->x + (buttonWidth + buttonHMargin) * (i % kButtonsInRow);
        buttons_[i].y = rect_->y + (buttonHeight + buttonVMargin) * (i / kButtonsInRow);
        buttons_[i].w = buttonWidth;
        buttons_[i].h = buttonHeight;
    }
    
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, rect_->w, buttonVSpace, 32, kPixelFormat);

    for(int i = 0; i < button_count_; ++i)
    {
        Uint64 delimiterPos = text_->find_first_of(" ");
        std::string foo = text_->substr(0, delimiterPos);
        *text_ = text_->substr(delimiterPos + 1);
        SDL_Surface *tempSurf = TTF_RenderText_Solid(font_, foo.c_str(), kTextColor);
        int textWidth;
        TTF_SizeText(font_, foo.c_str(), &textWidth, nullptr);
        SDL_Rect tempRect = {static_cast<int>(buttons_[i].x - rect_->x + buttonWidth / 2 - textWidth / 2), buttons_[i].y - rect_->y, 0, 0};
        SDL_BlitSurface(tempSurf, nullptr, surf, &tempRect);
        SDL_FreeSurface(tempSurf);
        
    }
    object_texture_ = SDL_CreateTextureFromSurface(renderer_, surf);
    SDL_FreeSurface(surf);
    SDL_QueryTexture(object_texture_, nullptr, nullptr, &rect_->w, &rect_->h);
}

void GameObject::changeTexture(Uint32 *_buffer, Uint32 _size)
{
    SDL_UpdateTexture(object_texture_, nullptr, _buffer, _size * sizeof(Uint32));
}

void GameObject::changeText(std::string _text)
{
    SDL_Surface *surf = TTF_RenderText_Solid(font_, _text.c_str(), kTextColor);
    SDL_Texture *tempTex = SDL_CreateTextureFromSurface(renderer_, surf);
    SDL_FreeSurface(surf);
    if(tempTex)
    {
        if(object_texture_) { SDL_DestroyTexture(object_texture_); }
        object_texture_ = tempTex;
        SDL_QueryTexture(object_texture_, nullptr, nullptr, &rect_->w, &rect_->h);
    }
}
