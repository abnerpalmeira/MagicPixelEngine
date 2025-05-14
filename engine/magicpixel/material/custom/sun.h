#pragma once

#include <algorithm>
#include "common/utility/random.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/material/attribute/movable.h"
#include "simulation/buffer.h"

class Sun : public MagicPixel {
private:
    static constexpr Uint32 MELTING_TEMPERATURE = 1000;
    static constexpr Uint32 VAPORIZATION_TEMPERATURE = 2000;
    static constexpr Uint32 MAX_TEMPERATURE = 5000;
    static constexpr Uint32 DEFAULT_TTL = 1000;
    static constexpr float HEAT_RADIUS = 5.0f;
    
    Color original_color_;
    void CreateSmoke(Buffer &buffer, int x, int y, const Color &color);
    void HeatSurroundings(Buffer &buffer, int x, int y);
    void TransformMaterial(Buffer &buffer, int x, int y);

public:
    Sun();
    void Update(Buffer &buffer, int x, int y) override;
};

namespace {
    std::unique_ptr<MagicPixel> CreateSun() {
        return std::make_unique<Sun>();
    }
    const bool registered_sun = MagicPixelFactory::Instance()->RegisterMagicPixel(MaterialType::SUN, CreateSun);
} 