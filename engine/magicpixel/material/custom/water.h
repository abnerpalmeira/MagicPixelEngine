//
//  water.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "simulation/buffer.h"
#include "magicpixel/material/base/liquid.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include  "common/utility/random.h"

class Water : public Liquid{
public:
    Water();
};

namespace{
    std::unique_ptr<MagicPixel> CreateWater(){
        return std::make_unique<Water>();
    }
    const bool registered_water = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::WATER, CreateWater);
}
