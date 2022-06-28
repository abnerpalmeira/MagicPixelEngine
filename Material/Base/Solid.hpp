//
//  Solid.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "Buffer.hpp"
#include "MagicPixel.hpp"
#include "MagicPixelFactory.hpp"
#include "MaterialType.hpp"
#include "Movable.hpp"
#include "Random.h"

class Solid : public Movable{
public:
    Solid();
    int CanMove(Buffer &buffer, int x, int y);
    void Update(Buffer &buffer,int x,int y);
private:
    void CelularAutomata(Buffer &buffer,int x,int y);
    void PhysicSimulation();
};

namespace{
    std::unique_ptr<MagicPixel> CreateSolid(){
        return std::make_unique<Solid>();
    }
    const bool registered_solid = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::SOLID, CreateSolid);
}

