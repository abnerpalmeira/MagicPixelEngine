#include <core/global.h>
#include <core/engine.h>
#include <core/game.h>


Engine *engine = nullptr;

int main(int argc, char **argv){
    engine = new Engine();
    while (engine->Running()) {
        engine->HandleEvents();
        engine->Update();
        engine->Render();
    }
    engine->Clear();
    return  0;
}
