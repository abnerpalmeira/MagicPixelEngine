//
//  button.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#pragma once

#include <string>
#include <functional>
#include <SDL.h>
#include "graphics/color.h"
#include "graphics/ui/ui_component.h"

class Button : public UIComponent{
public:
    Button();
    Button(SDL_Rect rect,Color background_color, std::function<void()> fn);
    ~Button();
    SDL_Surface* Surface();
    void OnClick(){}
    void OnHover(){}
protected:
    Color background_color_;
private:
    std::function<void()> fn_;
};

