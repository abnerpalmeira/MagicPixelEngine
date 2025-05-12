#pragma once

#include "simulation/buffer.h"
#include "magicpixel/material/base/liquid.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "common/utility/random.h"

class Lava : public Liquid {
public:
    Lava();
    void Update(Buffer &buffer, int x, int y);
private:
    static const int cooling_temperature = 200;
    static const int cooling_rate = 1;
};

namespace {
    std::unique_ptr<MagicPixel> CreateLava() {
        return std::make_unique<Lava>();
    }
    const bool registered_lava = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::LAVA, CreateLava);
} 