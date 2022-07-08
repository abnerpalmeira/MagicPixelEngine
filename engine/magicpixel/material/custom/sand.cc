//
//  sand.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "magicpixel/material/custom/sand.h"

Sand::Sand(){
    color_ = Color::Interpolate(Color(255,207,92,255), Color::Black, Random::DoubleOnInterval(0.0, 0.15));
    material_ = MaterialType::SAND;
}
