//
//  magic_pixel.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 01/06/22.
//

#pragma once

#include <memory>
#include "SDL2/SDL.h"
#include "Color.hpp"
#include "Global.hpp"
#include "Helper.hpp"
#include "MaterialType.hpp"
#include "Vector2.hpp"

class Buffer;
class MagicPixel{
public:
    MagicPixel();
    virtual ~MagicPixel(){}
    virtual void Update(Buffer &buffer,int x,int y){}
    Vector2 velocity_;
    Color color_;
    MaterialType material_;
    Uint32 surface_area_ = 15;
    Uint32 temperature_ = 0;
    Uint32 ignite_temperature_ = 0;
    Uint32 ttl_ = 0;
    int desinty_;
};