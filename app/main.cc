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
