//
//  rock.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "common/utility/random.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/magic_pixel_factory.h"
#include "magicpixel/material/base/static.h"

class Rock : public Static{
public:
    Rock();
};

namespace {
    std::unique_ptr<MagicPixel> CreateRock(){
        return std::make_unique<Rock>();
    }
    const bool registered_rock = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::ROCK, CreateRock);
}
