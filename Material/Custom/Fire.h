//
//  Fire.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#pragma once

#include <algorithm>
#include "Buffer.hpp"
#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "Movable.hpp"
#include "Random.h"

class Fire : public MagicPixel{
private:
    static Color color_array[3];
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
