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

class Button : virtual public UIComponent{
public:
    Button();
    Button(SDL_Rect rect,Color background_color, std::function<void()> fn);
    ~Button();
    SDL_Surface* GetUpdatedSurface();
    void OnClick();
    void OnHover();
protected:
    Color background_color_;
    std::function<void()> fn_;
private:
};

