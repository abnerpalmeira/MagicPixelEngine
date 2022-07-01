//
//  Static.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 28/06/22.
//

#include "Static.h"

Static::Static(){
    color_ = Color(128,128,128,255);
    if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Helper::RandomDoubleOnInterval(0.0, 0.15));
}

void Static::Update(){}
