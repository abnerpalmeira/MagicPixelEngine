//
//  Steam.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 25/06/22.
//

#include "Steam.h"

Steam::Steam(){
    color_ = Color(201,208,255,128);
    ttl_ = current_tick + Random::IntOnInterval(2000, 50000);
    material_ = MaterialType::STEAM;
    up_ = true;
}
