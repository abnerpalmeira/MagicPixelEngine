//
//  Water.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "Buffer.hpp"
#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "Movable.hpp"
#include "Random.hpp"

class Water : public Movable{
public:
    Water();
    int CanMove(Buffer &buffer, int x, int y);
    void CelularAutomata(Buffer &buffer,int x,int y);
    void Update(Buffer &buffer,int x,int y);
};

namespace{
    std::unique_ptr<MagicPixel> CreateWater(){
        return std::make_unique<Water>();
    }
    const bool registered_water = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::WATER, CreateWater);
}
