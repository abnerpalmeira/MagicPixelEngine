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
#include "GameObject.h"
#include "Texture.hpp"
#include "Button.hpp"
#include "Color.hpp"
#include "Global.hpp"
#include "Text.hpp"

class UI : public GameObject{
public:
    UI(SDL_Renderer *renderer, SDL_Rect rect, Color color);
    ~UI();
    void Update();
    void Click();
    void CreateTexture();
    void AddText(SDL_Rect text_rect, std::string text);
    void AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text, std::function<void(int)> fn);
    SDL_Rect rect_;
    std::vector<Text> text_;
private:
    Color color_;
    std::vector<ButtonGroup> button_group_;
};

#endif /* UI_hpp */
