//
//  water.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "Buffer.hpp"
#include "Liquid.hpp"
#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "Random.h"

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
