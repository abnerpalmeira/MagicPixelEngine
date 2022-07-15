//
//  game.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 31/05/22.
//

#pragma once

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <SDL.h>
#include "common/thread/thread_pool.h"
#include "core/camera.h"
#include "core/entity.h"
#include "core/global.h"
#include "core/input_manager.h"
#include "magicpixel/material/base/fire.h"
#include "magicpixel/material/base/gas.h"
#include "magicpixel/material/base/liquid.h"
#include "magicpixel/material/base/solid.h"
#include "magicpixel/material/base/static.h"
#include "magicpixel/material/custom/rock.h"
#include "magicpixel/material/custom/sand.h"
#include "magicpixel/material/custom/steam.h"
#include "magicpixel/material/custom/water.h"
#include "magicpixel/material/custom/wood.h"
#include "graphics/texture.h"
#include "graphics/ui.h"
#include "graphics/graphics.h"
#include "simulation/simulation.h"

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
    std::vector<Entity> entitys_; 
private:
    void CreateCamera();
    void CreateSimulation();
    void CreatePerfomanceBar();
    void CreateUI();
    void ResetVariables();
    void InitFont();
    SDL_Event e_;
    SDL_Point last_cursor_;
    Simulation *simulation_;
    Uint32 tick_count_;
    Uint16 draw_radius_;
    MaterialType material_;
    int count_;
    bool is_running_ = false;
    bool ui_mode_ = true;
    bool debug_mode_ = false;
    bool paused_ = false;
};
