//
//  UI.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <sstream>
#include <string>
#include "SDL2_ttf/SDL_ttf.h"
#include "Texture.hpp"
#include "Button.hpp"

class UI : public Texture{
public:
    UI(SDL_Renderer *renderer, float scale, SDL_Rect rect, const char *font_file);
    void AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text);
private:
    TTF_Font *font_;
    std::vector<ButtonGroup> button_group_;
};

#endif /* UI_hpp */
