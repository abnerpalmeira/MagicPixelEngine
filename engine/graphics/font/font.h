#include <string>
#include <unistd.h> // for getcwd()
#include <SDL_ttf.h>
#include "core/global.h"

#pragma once

class Font{
public:
    Font();
    Font(const char *font_file_path, int size);
    ~Font();
    TTF_Font* GetFont();
    std::string path_;
    int size_;
private:
};