//
//  text.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#include "text.h"

Text::Text(){

}

Text::Text(SDL_Rect rect, Color color, std::string text, char *font_file_path, int size){
    rect_ = rect;
    text_ = text;
    color_ = color;
    font_ = Font(font_file_path,size);
    surface_ = Surface();
}

SDL_Surface* Text::Surface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    SDL_Surface *temp_surf = TTF_RenderText_Solid(font_.GetFont(), text_.c_str(), color_.GetSDLColor());
    int x = rect_.x + ((rect_.w + temp_surf->w)/2 - temp_surf->w);
    int y = rect_.y + ((rect_.h + temp_surf->h)/2 - temp_surf->h);
    SDL_Rect temp_rect = {x,y,temp_surf->w,temp_surf->h};
    SDL_BlitSurface(temp_surf, nullptr, surf, &temp_rect);
    SDL_FreeSurface(temp_surf);
    return surf;
}

void Text::SetColor(Color color){
    color_ = color;
    surface_ = Surface();
}

void Text::SetFont(char *font_file_path, int size){
    font_ = Font(font_file_path,size);
    surface_ = Surface();
}

void Text::SetText(std::string text){
    text_ = text;
    surface_ = Surface();
}
