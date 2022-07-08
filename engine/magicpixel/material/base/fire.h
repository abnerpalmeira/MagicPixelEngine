//
//  fire.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#pragma once

#include <algorithm>
#include "simulation/buffer.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/material/attribute/movable.h"
#include "common/utility/navigation.h"
#include "common/utility/random.h"

class Fire : public MagicPixel{
private:
    static Color colors[3];
    static Uint32 min_temperature;
    static Uint32 max_temperature;
    static Uint32 default_ttl;
public:
    Fire();
    void Update(Buffer &buffer,int x,int y);
};

namespace{
    std::unique_ptr<MagicPixel> CreateFire(){
        return std::make_unique<Fire>();
    }
    const bool registered_steam = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::FIRE, CreateFire);
}
