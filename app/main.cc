#include <core/engine.h>
#include <core/game.h>
#include <core/global.h>
#include <core/input_manager.h>
#include <core/renderer.h>
#include <core/window.h>
#include <SDL.h>
#include <SDL_ttf.h>



Engine *engine = nullptr;
Game *game = nullptr;

void run_engine(){
    engine = new Engine();
    while (engine->Running()) {
        engine->HandleEvents();
        engine->Update();
        engine->Render();
    }
    engine->Clear();
}

void run_game(){
    game = new Game("Magic Pixel Engine",0,0,kScreenWidth, kScreenHeight,false);
    while (game->Running()) {
        game->HandleEvents();
        game->Update();
        game->Render();
    }
    game->Clean();
}

int main(int argc, char **argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    InputManager::Instance();
    Window::Instance();
    SDL_SetRenderDrawBlendMode(Renderer::Instance()->renderer_, SDL_BLENDMODE_BLEND);
    run_game();
    // SDL_DestroyWindow(window_);
    // SDL_DestroyRenderer(renderer_);
    SDL_Quit();
    return  0;
}
