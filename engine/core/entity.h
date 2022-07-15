//
//  entity.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 01/06/22.
//

#pragma once

#include <stdio.h>
#include <string>
#include <SDL.h>
#include "core/input_manager.h"
#include "graphics/texture.h"
#include "simulation/simulation.h"

class Entity{
public:
    Entity();
    virtual ~Entity(){}
    bool Enabled();
    virtual bool IsClicked(){return false;}
    virtual void Click(){}
    virtual void Update(){}
    virtual void Render(){}
protected:
    bool enabled_ = true;
    SDL_Rect rect_ = {0,0,0,0};
private:
};