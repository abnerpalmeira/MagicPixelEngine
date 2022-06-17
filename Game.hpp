//
//  Game.hpp
//  MagicPixel
//
//  Created by Abner Palmeira on 31/05/22.
//

#ifndef Game_hpp
#define Game_hpp
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <unistd.h>
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_image/SDL_image.h"
#include "ECS.hpp"
#include "Components.hpp"
#include "Texture.hpp"
#include "Simulation.hpp"
#include "Global.hpp"
#include "ThreadPool.hpp"
#include "GameObject.hpp"

class Game{
public:
    Game(const char *title, int x, int y, int w, int h, bool fullscreen);
    ~Game();
    void KeyPressed(SDL_Event e);
    void MousePressed(SDL_Event e);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool Running(){return is_running_;}
    static SDL_Renderer *renderer_;
private:
    void Init(const char* title,int x,int y,int width,int height,bool fullscreen);
    void CreateSimulation();
    void CreateViewPort();
    void PerformanceBar();
    void CreateToolUI();
    void CreateMaterialUI();
    void ResetVariables();
    bool is_running_ = false;
    bool toggle_ = true;
    bool draw_rad_changed_;
    bool debug_mode_ = false;
    bool mbr_pressed_ = false;
    bool mbr_held_ = false;
    bool mbl_pressed_ = false;
    bool mbl_held_ = false;
    bool paused_ = false;
    bool quit_ = false;
    int count_;
    SDL_Texture *background;
    Uint32 tick_count_;
    Uint16 draw_radius_;
    MaterialType material_;
    SDL_Event e_;
    SDL_Point cursor_;
    SDL_Point last_cursor_;
    GameObject *simulation_;
    GameObject *viewport_;
    GameObject *performance_bar_;
    GameObject *tools_ui_;
    GameObject *material_ui_;
    TTF_Font *font_;
    SDL_Window *window_;
};

#endif /* Game_hpp */
