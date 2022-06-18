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
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Button.hpp"
#include "Color.hpp"

class UI : public GameObject{
public:
    UI(SDL_Renderer *renderer, SDL_Rect rect, Color color);
    ~UI();
    void AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,const char *font_file);
private:
    void CreateTexture();
    Color color_;
    SDL_Rect rect_;
    std::vector<ButtonGroup> button_group_;
};

#endif /* UI_hpp */
