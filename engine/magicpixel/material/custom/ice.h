#pragma once

#include "simulation/buffer.h"
#include "magicpixel/material/base/solid.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "common/utility/random.h"

class Ice : public Solid {
public:
    Ice();
    void Update(Buffer &buffer, int x, int y);
private:
    static const int melt_temperature = 100;
};

namespace {
    std::unique_ptr<MagicPixel> CreateIce() {
        return std::make_unique<Ice>();
    }
    const bool registered_ice = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::ICE, CreateIce);
} 