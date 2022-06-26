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

class Wood : public MagicPixel{
public:
    Wood();
    void Update();
    bool CanMove(int idx);
};

namespace{
    std::unique_ptr<MagicPixel> CreateWood(){
        return std::make_unique<Wood>();
    }
    const bool registered_wood = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::WOOD, CreateWood);
}

