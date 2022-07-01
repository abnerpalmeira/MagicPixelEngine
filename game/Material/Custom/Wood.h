//
//  Wood.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#pragma once

#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "MagicPixelFactory.hpp"
#include "Static.h"

class Wood : public Static{
public:
    Wood();
};

namespace{
    std::unique_ptr<MagicPixel> CreateWood(){
        return std::make_unique<Wood>();
    }
    const bool registered_wood = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::WOOD, CreateWood);
}

