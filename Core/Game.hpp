//
//  Game.hpp
//  MagicPixel
//
//  Created by Abner Palmeira on 31/05/22.
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <unistd.h>
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_image/SDL_image.h"
#include "Simulation.hpp"
#include "Global.hpp"
#include "ThreadPool.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Texture.hpp"
#include "UI.hpp"

class Game{
public:
    Game(const char *title, int x, int y, int w, int h, bool fullscreen);
    ~Game();
    void HandleEvents();
    void PreUpdate();
    void Update();
    void LateUpdate();
    void Render();
    void Clean();
    void SetMaterial(int material);
    bool Running();
    void Pause(int x);
    void ResetSimulation(int x);
    static SDL_Renderer *renderer_;
private:
    void Init(const char* title,int x,int y,int width,int height);
    void CreateSimulation();
    void CreateViewPort();
    void CreatePerfomanceBar();
    void CreateUI();
    void ResetVariables();
    void InitFont();
    SDL_Event e_;
    SDL_Point last_cursor_;
    SDL_Window *window_;
    Simulation *simulation_;
    GameObject *viewport_;
    UI *performance_bar_;
    UI *ui_;
    UI *material_ui_;
    Uint32 tick_count_;
    Uint16 draw_radius_;
    MaterialType material_;
    int count_;
    bool is_running_ = false;
    bool ui_mode_ = true;
    bool debug_mode_ = false;
    bool paused_ = false;
};
