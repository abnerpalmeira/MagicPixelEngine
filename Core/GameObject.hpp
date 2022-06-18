//
//  GameObject.hpp
//  MagicPixel
//
//  Created by Abner Palmeira on 01/06/22.
//

#ifndef GameObject_hpp
#define GameObject_hpp
#include <stdio.h>
#include <string>
#include "SDL2/SDL.h"
#include "Simulation.hpp"
#include "Texture.hpp"

class GameObject{
public:
    GameObject();
//    ~GameObject();
    void Update();
    void Render();
    Texture *texture_;
    Uint32 *draw_buffer_;
    SDL_Renderer *renderer_;
private:
};

#endif /* GameObject_hpp */