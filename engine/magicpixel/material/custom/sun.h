#pragma once

#include <algorithm>
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"
#include "magicpixel/material/attribute/movable.h"
#include "common/utility/navigation.h"
#include "simulation/buffer.h"

class Sun : public MagicPixel {
private:
    static constexpr Uint32 MELTING_TEMPERATURE = 300;
    static constexpr Uint32 VAPORIZATION_TEMPERATURE = 800;
    static constexpr Uint32 MAX_TEMPERATURE = 1000;
    static constexpr float HEAT_RADIUS = 2.0f;
    static constexpr int FLAME_HEIGHT = 3;
    
    Color original_color_;
    static Color colors[3];  // Fire-like colors
    static Uint32 min_temperature;
    static Uint32 max_temperature;
    static Uint32 default_ttl;
    
    void CreateSmoke(Buffer &buffer, int x, int y, const Color &color);
    void HeatSurroundings(Buffer &buffer, int x, int y);
    void TransformMaterial(Buffer &buffer, int x, int y);
    void CreateFlameParticle(Buffer &buffer, int x, int y, int height);

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