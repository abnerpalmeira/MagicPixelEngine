#pragma once

#include <stdio.h>
#include <string>
#include <SDL.h>
#include "core/entity.h"
#include "core/input_manager.h"
#include "graphics/texture.h"

class Camera : public Entity{
public:
    Camera(float scale, SDL_Rect rect);
    ~Camera();
    bool IsClicked();
    void Click();
    void Update();
    void Render();
    Texture texture_;
    Uint32 *draw_buffer_;
private:
};