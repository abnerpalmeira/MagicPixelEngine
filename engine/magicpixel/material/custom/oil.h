#pragma once

#include "simulation/buffer.h"
#include "magicpixel/material/base/liquid.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "common/utility/random.h"

class Oil : public Liquid {
public:
    Oil();
    void Update(Buffer &buffer, int x, int y);
};

namespace {
    std::unique_ptr<MagicPixel> CreateOil() {
        return std::make_unique<Oil>();
    }
    const bool registered_oil = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::OIL, CreateOil);
} 