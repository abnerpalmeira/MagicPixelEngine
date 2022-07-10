#include <core/global.h>
#include <core/engine.h>
#include <core/game.h>


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
    run_game();
    return  0;
}
