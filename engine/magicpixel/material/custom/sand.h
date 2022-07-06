//
//  sand.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "Buffer.hpp"
#include "MagicPixel.hpp"
#include "MagicPixelFactory.hpp"
#include "MaterialType.hpp"
#include "Solid.hpp"
#include "Random.h"

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
