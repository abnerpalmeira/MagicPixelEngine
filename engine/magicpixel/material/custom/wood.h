//
//  wood.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#pragma once

#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/magic_pixel_factory.h"
#include "magicpixel/material/base/static.h"

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

