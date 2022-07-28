#include "button_text.h"

ButtonText::ButtonText(SDL_Rect rect,Color background_color, Color text_color, std::string text, char *font_file_path, int size, std::function<void()> fn){
    rect_ = rect;
    background_color_ = background_color;
    text_ = text;
    color_ = text_color;
    font_ = Font(font_file_path,size);
    fn_ = fn;
    surface_ = GetUpdatedSurface();
}

SDL_Surface* ButtonText::GetUpdatedSurface(){
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, rect_.w, rect_.h, 32, kPixelFormat);
    SDL_FillRect(surf, NULL, background_color_.GetSDLMap());
    SDL_Surface *temp_surf = TTF_RenderText_Solid(font_.GetFont(), text_.c_str(), color_.GetSDLColor());
    int x = rect_.x + ((rect_.w + temp_surf->w)/2 - temp_surf->w);
    int y = rect_.y + ((rect_.h + temp_surf->h)/2 - temp_surf->h);
    SDL_Rect temp_rect = {x,y,temp_surf->w,temp_surf->h};
    SDL_BlitSurface(temp_surf, nullptr, surf, &temp_rect);
    SDL_FreeSurface(temp_surf);
    return surf;
}