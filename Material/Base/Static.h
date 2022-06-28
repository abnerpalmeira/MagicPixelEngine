//
//  Static.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 28/06/22.
//

#pragma once

#include "MagicPixel.hpp"
#include "MaterialType.hpp"
#include "MagicPixelFactory.hpp"

class Static : public MagicPixel{
public:
    Static();
    void Update();
};

namespace{
    std::unique_ptr<MagicPixel> CreateStatic(){
        return std::make_unique<Static>();
    }
    const bool registered_static = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::STATIC, CreateStatic);
}
