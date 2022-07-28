//
//  text.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#include "text.h"

Text::Text(){

}

Text::Text(SDL_Rect rect, Color color, std::string text, const char *font_file_path, int size){
    rect_ = rect;
    text_ = text;
    color_ = color;
    font_ = Font(font_file_path,size);
    surface_ = GetUpdatedSurface();
}

SDL_Surface* Text::GetUpdatedSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    TTF_Font *font = font_.GetFont();
    SDL_Surface *temp_surf = TTF_RenderText_Solid(font, text_.c_str(), color_.GetSDLColor());
    int x = rect_.x + ((rect_.w + temp_surf->w)/2 - temp_surf->w);
    int y = rect_.y + ((rect_.h + temp_surf->h)/2 - temp_surf->h);
    SDL_Rect temp_rect = {x,y,temp_surf->w,temp_surf->h};
    SDL_BlitSurface(temp_surf, nullptr, surf, &temp_rect);
    TTF_CloseFont(font);
    SDL_FreeSurface(temp_surf);
    return surf;
}

void Text::SetColor(Color color){
    color_ = color;
    surface_ = GetUpdatedSurface();
}

void Text::SetFont(char *font_file_path, int size){
    font_ = Font(font_file_path,size);
    surface_ = GetUpdatedSurface();
}

void Text::SetText(std::string text){
    text_ = text;
    surface_ = GetUpdatedSurface();
}
