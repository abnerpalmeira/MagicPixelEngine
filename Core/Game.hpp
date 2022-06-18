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
    void KeyPressed(SDL_Event e);
    void MousePressed(SDL_Event e);
    void HandleEvents();
    void PreUpdate();
    void Update();
    void Render();
    void Clean();
    bool Running(){return is_running_;}
    static SDL_Renderer *renderer_;
private:
    InputManager input_manager_;
    void Init(const char* title,int x,int y,int width,int height,bool fullscreen);
    void CreateSimulation();
    void CreateViewPort();
    void CreatePerfomanceBar();
    void CreateUI();
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
    Simulation *simulation_;
    GameObject *viewport_;
    UI *performance_bar_;
    UI *ui_;
    UI *material_ui_;
    SDL_Window *window_;
};

#endif /* Game_hpp */
