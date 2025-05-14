//
//  rock.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//

#include "magicpixel/material/custom/rock.h"
#include "magicpixel/material/custom/lava.h"
#include "common/utility/navigation.h"

Rock::Rock() {
    color_ = Color(58, 50, 50, 255);
    material_ = MaterialType::ROCK;
    if(Random::CoinToss()) {
        color_ = Color::Interpolate(color_, Color::White, Random::DoubleOnInterval(0.0, 0.15));
    }
}

void Rock::Update(Buffer &buffer, int x, int y) {
    // Check if it should melt
    if (temperature_ >= melt_temperature) {
        buffer.ReplacMagicPixel(MaterialType::LAVA, x, y);
        return;
    }
    
    // Heat up from nearby heat sources
    for (int i = 0; i < 8; i++) {
        int a = x + Navigation::dx[i], b = y + Navigation::dy[i];
        if (a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        
        if (!buffer.IsCellEmpty(a, b)) {
            MaterialType neighbor = buffer.GetMaterial(a, b);
            if (neighbor == MaterialType::FIRE || neighbor == MaterialType::SUN || neighbor == MaterialType::LAVA) {
                buffer.buffer_[a][b].TransferHeat(temperature_);
            }
        }
    }
    
    // Call parent class Update
    MagicPixel::Update(buffer, x, y);
}
