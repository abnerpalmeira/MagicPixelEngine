//
//  steam.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 25/06/22.
//

#pragma once

#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "Gas.hpp"
#include "Random.h"

class Steam : public Gas{
public:
    Steam();
};

namespace{
    std::unique_ptr<MagicPixel> CreateSteam(){
        return std::make_unique<Steam>();
    }
    const bool registered_steam = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::STEAM, CreateSteam);
}
