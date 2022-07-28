//
//  text.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 19/06/22.
//

#pragma once

#include <string>
#include <SDL.h>
#include "core/global.h"
#include "graphics/color.h"
#include "graphics/font/font.h"
#include "graphics/ui/ui_component.h"

class Text : virtual public UIComponent{
public:
    Text();
    Text(SDL_Rect rect, Color color, std::string text, const char *font_file_path, int size);
    SDL_Surface* GetUpdatedSurface();
    void SetColor(Color color);
    void SetFont(char *font_file_path, int size);
    void SetText(std::string text);
protected:
    Color color_;
    Font font_;
    std::string text_;
private:
};
