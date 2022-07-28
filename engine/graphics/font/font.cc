#include "font.h"

Font::Font(){}

std::string GetCurrentWorkingDir()
{
    std::string cwd("\0",FILENAME_MAX+1);
    return getcwd(&cwd[0],cwd.capacity());
}

Font::Font(const char *font_file_path, int size){
    path_ = font_file_path;
    size_ = size;
}

Font::~Font(){
}

TTF_Font* Font::GetFont(){
    return TTF_OpenFont(path_.c_str(), size_);
}


