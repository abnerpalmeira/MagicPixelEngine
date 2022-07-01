//
//  Rock.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "MagicPixelFactory.hpp"
#include "Static.h"

class Rock : public Static{
public:
    Rock();
};

namespace{
    std::unique_ptr<MagicPixel> CreateRock(){
        return std::make_unique<Rock>();
    }
    const bool registered_rock = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::ROCK, CreateRock);
}
