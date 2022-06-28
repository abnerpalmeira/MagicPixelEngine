//
//  Gas.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "Gas.hpp"


Gas::Gas(){
//    color_ = Color(128,128,128,128);
    material_ = MaterialType::GAS;
    up_ = true;
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
    if(up_ && MoveStep(buffer,4, Orientation::UP,x,y)) return;
    if(MoveStep(buffer,1, Orientation::DOWN,x,y)) return;
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
