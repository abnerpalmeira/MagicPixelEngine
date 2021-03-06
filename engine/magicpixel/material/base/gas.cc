//
//  gas.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "magicpixel/material/base/gas.h"


Gas::Gas(){
    color_ = Color(128,128,128,128);
    material_ = MaterialType::GAS;
    up_ = true;
    dispersion_rate_ = 2;
    oscillation_rate_ = 1;
}
    
int Gas::CanMove(Buffer &buffer, int x, int y){
    if(buffer.IsCellEmpty(x, y)){
        return 1;
    }
    else if(buffer.buffer_[x][y].magic_pixel_ptr_->material_ == material_){
        return -1;
    }
    return 0;
}

void Gas::CelularAutomata(Buffer &buffer, int x, int y){
    if(up_ && MoveStep(buffer,dispersion_rate_, Orientation::UP,x,y)) return;
    if(oscillation_rate_ && MoveStep(buffer,oscillation_rate_, Orientation::DOWN,x,y)) return;
    if(Random::CoinToss()){
        if(MoveStep(buffer,1, Orientation::UP_RIGHT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::UP_LEFT,x,y)) return;
    }
    else{
        if(MoveStep(buffer,1, Orientation::UP_LEFT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::UP_RIGHT,x,y)) return;
    }
}

void Gas::Update(Buffer &buffer, int x, int y){
    CelularAutomata(buffer,x,y);
    up_ = !up_;
}
