#include <SDL.h>
#include "button.h"
#include "core/global.h"
#include "graphics/color.h"
#include "graphics/ui/ui_component.h"

#pragma once

class ButtonGroup : public UIComponent{
public:
    ButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,std::function<void(int)> fn);
    ~ButtonGroup();
    SDL_Surface* ToSurface();
    SDL_Rect rect_;
    void Click();
private:
    std::vector<Button> buttons_;
};