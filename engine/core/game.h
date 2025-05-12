//
//  game.h
//  MagicPixelEngine
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
#include <SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>
#include "common/thread/thread_pool.h"
#include "core/game_object.h"
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
#include "magicpixel/material/custom/oil.h"
#include "magicpixel/material/custom/ice.h"
#include "magicpixel/material/custom/lava.h"
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
private:
    void Init(const char* title,int x,int y,int width,int height);
    void CreateSimulation();
    void CreateViewPort();
    void CreatePerfomanceBar();
    void CreateUI();
    void ResetVariables();
    void InitFont();
    void ShowMainMenuBar();
    void ShowMaterialPanel();
    void ShowPerformancePanel();
    void ShowDebugPanel();
    
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
    bool show_material_panel_ = true;
    bool show_performance_panel_ = true;
    bool show_debug_panel_ = false;
    ImVec4 clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
