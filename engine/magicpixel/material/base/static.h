//
//  static.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 28/06/22.
//

#pragma once

#include "core/global.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/magic_pixel_factory.h"
#include "common/utility/random.h"

class Static : public MagicPixel{
public:
    Static();
    virtual void Update(Buffer &buffer, int x, int y) override;
};

namespace{
    std::unique_ptr<MagicPixel> CreateStatic(){
        return std::make_unique<Static>();
    }
    const bool registered_static = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::STATIC, CreateStatic);
}
