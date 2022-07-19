#include <SDL.h>
#include "button.h"
#include "core/global.h"
#include "graphics/color.h"
#include "graphics/ui/ui_component.h"

#pragma once

class ButtonGroup : public UIComponent{
public:
    ButtonGroup(SDL_Rect rect_);
    ~ButtonGroup();
    SDL_Surface* Surface();
    void AddButtons(std::vector<Button> buttons);
    void Click();
private:
    std::vector<Button> buttons_;
};