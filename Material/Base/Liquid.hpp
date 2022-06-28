//
//  Liquid.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//
#pragma once

#include "Buffer.hpp"
#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "Movable.hpp"
#include "Random.h"

class Liquid : public Movable{
protected:
    int dispersion_rate_;
public:
    Liquid();
    int CanMove(Buffer &buffer, int x, int y);
    void CelularAutomata(Buffer &buffer,int x,int y);
    void Update(Buffer &buffer,int x,int y);
};

namespace{
    std::unique_ptr<MagicPixel> CreateLiquid(){
        return std::make_unique<Liquid>();
    }
    const bool registered_liquid = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::LIQUID, CreateLiquid);
}
