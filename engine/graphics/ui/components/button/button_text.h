#pragma once


#include <SDL.h>
#include "button.h"
#include "graphics/ui/components/text/text.h"

class ButtonText : public Button{
public:
    ButtonText(SDL_Rect rect,Color background_color, Color text_color, std::string text, char *font_file_path, int size, std::function<void()> fn);
    ~ButtonText();
    SDL_Surface* Surface();
    void OnHover(){}
private:
    Text text_;
};

