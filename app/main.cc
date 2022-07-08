#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <core/engine.h>
// #include "editor/Engine.h"
//#include <SDL.h>
//#include <SDL.h>
//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_sdlrenderer.h"
//#include "Game.h"
//#include "common/thread/thread_pool.h"
//#include "Simulation.hpp"
//#include "core/global.h"


Engine *engine = nullptr;

int main(int argc, char **argv){
    std::cout << "Hello World" << std::endl;
    engine = new Engine();
    while (engine->Running()) {
        engine->HandleEvents();
        engine->Update();
        engine->Render();
    }
    engine->Clear();
    return  0;
}
