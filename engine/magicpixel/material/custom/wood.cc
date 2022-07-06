//
//  wood.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#include "wood.h"

Wood::Wood(){
    color_ = Color(106,75,63,255);
    ignite_temperature_ = 250;
    surface_area_ = 80;
    material_ = MaterialType::WOOD;
    if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::Black, Helper::RandomDoubleOnInterval(0.0, 0.4));
}
