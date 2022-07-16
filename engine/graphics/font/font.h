#include <SDL_ttf.h>

#pragma once

class Font{
public:
    Font();
    Font(char *font_file_path, int size);
    ~Font();
    TTF_Font* GetFont();
private:
    TTF_Font *font_ = nullptr;
};