//
//  static.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 28/06/22.
//

#include "magicpixel/material/base/static.h"

Static::Static(){
    color_ = Color(128,128,128,255);
    // if(Random::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Random::DoubleOnInterval(0, 0.15));
}

void Static::Update(){}
