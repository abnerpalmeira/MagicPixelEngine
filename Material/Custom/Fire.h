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
#include "Navigation.h"
#include "Random.h"

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
