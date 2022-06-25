//
//  Sand.hpp
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
#include "Random.hpp"

class Sand : public Movable{
public:
    Sand();
    int CanMove(Buffer &buffer, int x, int y);
    void Update(Buffer &buffer,int x,int y);
private:
    void CelularAutomata(Buffer &buffer,int x,int y);
    void PhysicSimulation();
};

namespace{
    std::unique_ptr<MagicPixel> CreateSand(){
        return std::make_unique<Sand>();
    }
    const bool registered_sand = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::SAND, CreateSand);
}
