//
//  water.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//

#include "magicpixel/material/custom/water.h"

Water::Water(){
    color_ = Color(131,215,238,180);
    material_ = MaterialType::WATER;
    dispersion_rate_ = 5;
}
