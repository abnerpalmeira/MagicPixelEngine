#pragma once

#include <stdio.h>
#include <string>
#include <SDL.h>
#include "core/game_object.h"
#include "core/input_manager.h"
#include "graphics/texture.h"

class Camera : public GameObject{
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