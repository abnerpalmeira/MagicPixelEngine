#include "magicpixel/material/custom/ice.h"

Ice::Ice() {
    color_ = Color(200, 200, 255, 255);
    material_ = MaterialType::ICE;
    desinty_ = 1;
    if(Random::CoinToss()) {
        color_ = Color::Interpolate(color_, Color::White, Random::DoubleOnInterval(0.0, 0.2));
    }
}

void Ice::Update(Buffer &buffer, int x, int y) {
    // Check if it should melt
    if (temperature_ >= melt_temperature) {
        buffer.ReplacMagicPixel(MaterialType::WATER, x, y);
        return;
    }
    
    // Heat up from nearby fire or lava
    for (int i = 0; i < 8; i++) {
        int a = x + dx_[i], b = y + dy_[i];
        if (a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        
        if (!buffer.IsCellEmpty(a, b)) {
            MaterialType neighbor = buffer.GetMaterial(a, b);
            if (neighbor == MaterialType::FIRE) {
                temperature_ += 5;
            } else if (neighbor == MaterialType::LAVA) {
                temperature_ += 20;
            }
        }
    }
    
    // Call Solid's Update to handle movement
    Solid::Update(buffer, x, y);
} 