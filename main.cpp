#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "Game.hpp"
#include "ThreadPool.hpp"
#include "Simulation.hpp"
#include "Graphics.hpp"
#include "Global.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

Game *game = nullptr;

int main(int argc, char **argv){
        game = new Game("Magic Pixel Engine",0,0,kScreenWidth, kScreenHeight,false);
        while (game->Running()) {
            game->HandleEvents();
            game->Update();
            game->Render();
        }
        game->Clean();
        return  0;
}
