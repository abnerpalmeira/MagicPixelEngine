//
// ui.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#pragma once

#include <stdio.h>
#include <sstream>
#include <string>
#include <SDL.h>
#include "core/game_object.h"
#include "graphics/texture.h"
#include "graphics/button.h"
#include "graphics/color.h"
#include "core/global.h"
#include "graphics/text.h"

class UI : public GameObject{
public:
    UI(SDL_Rect rect, Color color);
    void Update();
    void Click();
    void CreateTexture();
    void AddText(SDL_Rect text_rect, std::string text);
    void AddButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text, std::function<void(int)> fn);
    std::vector<Text> text_;
    Texture texture_;
private:
    Color color_;
    std::vector<ButtonGroup> button_group_;
};
