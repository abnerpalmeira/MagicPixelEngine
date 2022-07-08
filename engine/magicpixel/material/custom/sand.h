//
//  sand.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "simulation/buffer.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/magic_pixel_factory.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/material/base/solid.h"
#include  "common/utility/random.h"

class Sand : public Solid{
public:
    Sand();
};

namespace{
    std::unique_ptr<MagicPixel> CreateSand(){
        return std::make_unique<Sand>();
    }
    const bool registered_sand = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::SAND, CreateSand);
}
