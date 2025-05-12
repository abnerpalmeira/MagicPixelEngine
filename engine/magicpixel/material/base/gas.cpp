//
//  gas.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/attribute/movable.h"
#include  "common/utility/random.h"


class Gas : public Movable{
protected:
    int dispersion_rate_;
    int oscillation_rate_;
    bool up_;
public:
    Gas();
    int CanMove(Buffer &buffer, int x, int y);
    void CelularAutomata(Buffer &buffer,int x,int y);
    void Update(Buffer &buffer,int x,int y);
};

namespace{
    std::unique_ptr<MagicPixel> CreateGas(){
        return std::make_unique<Gas>();
    }
    const bool registered_gas = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::GAS, CreateGas);
}

