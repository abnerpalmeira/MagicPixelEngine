#include "magicpixel/material/custom/lava.h"

Lava::Lava() {
    color_ = Color(255, 100, 0, 255);
    material_ = MaterialType::LAVA;
    dispersion_rate_ = 1;
    temperature_ = 1000;
    desinty_ = 3; // Higher density than water and oil
}

void Lava::Update(Buffer &buffer, int x, int y) {
    // Cool down over time
    if (temperature_ > cooling_temperature) {
        temperature_ -= cooling_rate;
    } else {
        buffer.ReplacMagicPixel(MaterialType::ROCK, x, y);
        return;
    }

    // Heat up and potentially ignite nearby materials
    for (int i = 0; i < 8; i++) {
        int a = x + dx_[i], b = y + dy_[i];
        if (a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        
        if (buffer.Ignites(a, b, temperature_)) {
            buffer.ReplacMagicPixel(MaterialType::FIRE, a, b);
        } else if (!buffer.IsCellEmpty(a, b)) {
            MaterialType neighbor = buffer.GetMaterial(a, b);
            if (neighbor == MaterialType::WATER) {
                buffer.ReplacMagicPixel(MaterialType::STEAM, a, b);
            } else if (neighbor == MaterialType::ICE) {
                buffer.ReplacMagicPixel(MaterialType::WATER, a, b);
            } else {
                buffer.buffer_[a][b].TransferHeat(temperature_);
            }
        }
    }

    // Update color based on temperature
    float temp_ratio = (float)(temperature_ - cooling_temperature) / (1000 - cooling_temperature);
    color_ = Color::Interpolate(Color(255, 100, 0, 255), Color(150, 50, 0, 255), 1.0f - temp_ratio);

    // Call Liquid's Update to handle movement
    Liquid::Update(buffer, x, y);
} 