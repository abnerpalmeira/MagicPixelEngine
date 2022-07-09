//
//  rock.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//

#include "magicpixel/material/custom/rock.h"

Rock::Rock(){
    color_ = Color(58,50,50,255);
    if(Random::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Random::DoubleOnInterval(0.0, 0.15));
}
