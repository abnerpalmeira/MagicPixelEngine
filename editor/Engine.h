//
//  Engine.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 01/07/22.
//

#pragma once

#include "SDL2/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "widgets/Hierarchy.h"
#include "widgets/Inspector.h"
#include "widgets/Viewer.h"

class Engine{
public:
    Engine();
    bool Running();
    void Clear();
    void HandleEvents();
    void Update();
    void Render();
    void ShowAppMainMenuBar();
private:
    ImVec4 clear_color;
    SDL_Renderer* renderer_;
    SDL_Window* window_;
    bool is_running_;
    bool show_demo_window;
    bool show_another_window;
};
