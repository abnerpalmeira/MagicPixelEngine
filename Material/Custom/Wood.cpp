//
//  Wood.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#include "Wood.h"

Wood::Wood(){
    color_ = Color(58,50,50,255);
    ignite_temperature_ = 250;
    if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::Black, Helper::RandomDoubleOnInterval(0.0, 0.15));
}

void Wood::Update(){}
    
bool Wood::CanMove(int idx){
    return true;
}
