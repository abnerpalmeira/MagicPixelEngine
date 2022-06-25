//
//  Rock.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//

#include "Rock.hpp"

Rock::Rock(){
    color_ = Color(58,50,50,255);
    if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Helper::RandomDoubleOnInterval(0.0, 0.15));
}

void Rock::Update(){}
    
bool Rock::CanMove(int idx){
    return true;
}
