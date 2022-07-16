#include "font.h"

Font::Font(){}

Font::Font(char *font_file_path, int size){
    TTF_Init();
    font_ = TTF_OpenFont(font_file_path, size);
}

Font::~Font(){
    TTF_CloseFont(font_);
}

TTF_Font* Font::GetFont(){
    return font_;
}


