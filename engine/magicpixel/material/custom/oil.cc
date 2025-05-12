#include "magicpixel/material/custom/oil.h"

Oil::Oil() {
    color_ = Color(50, 50, 50, 200);
    material_ = MaterialType::OIL;
    dispersion_rate_ = 2;
    ignite_temperature_ = 150;
    surface_area_ = 30;
    desinty_ = 2; // Higher density than water
}

void Oil::Update(Buffer &buffer, int x, int y) {
    // Check if it should ignite
    if (temperature_ >= ignite_temperature_) {
        buffer.ReplacMagicPixel(MaterialType::FIRE, x, y);
        return;
    }
    
    // Heat up from nearby fire
    for (int i = 0; i < 8; i++) {
        int a = x + dx_[i], b = y + dy_[i];
        if (a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        
        if (!buffer.IsCellEmpty(a, b)) {
            MaterialType neighbor = buffer.GetMaterial(a, b);
            if (neighbor == MaterialType::FIRE) {
                temperature_ += 10;
            }
        }
    }
    
    // Call Liquid's Update to handle movement
    Liquid::Update(buffer, x, y);
} 