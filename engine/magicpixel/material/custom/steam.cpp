//
//  steam.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 25/06/22.
//

#pragma once

#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/material/base/gas.h"
#include  "common/utility/random.h"

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
