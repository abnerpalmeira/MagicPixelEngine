//
//  Steam.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 25/06/22.
//

#pragma once

#include "Buffer.hpp"
#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "Movable.hpp"
#include "Random.h"


class Steam : public Movable{
private:
    bool up_;
public:
    Steam();
    int CanMove(Buffer &buffer, int x, int y);
    void CelularAutomata(Buffer &buffer,int x,int y);
    void Update(Buffer &buffer,int x,int y);
};

namespace{
    std::unique_ptr<MagicPixel> CreateSteam(){
        return std::make_unique<Steam>();
    }
    const bool registered_steam = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::STEAM, CreateSteam);
}
