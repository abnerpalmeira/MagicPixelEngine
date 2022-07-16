//
// ui.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#pragma once

#include <vector>
#include <SDL.h>
#include "core/entity.h"
#include "graphics/texture.h"
#include "graphics/color.h"
#include "graphics/ui/ui_component.h"
#include "core/global.h"

class UI : public Entity{
public:
    UI(SDL_Rect rect, Color background_color = Color(128,128,128,0));
    void AddComponent(UIComponent &ui_component);
    void Update();
    void Render();
    void UpdateTexture();
private:
    std::vector<UIComponent> ui_components_;
    Color background_color_;
    Texture texture_;
};
