//
//  Steam.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 25/06/22.
//

#include "Steam.h"

Steam::Steam(){
    color_ = Color(201,208,210,128);
//    color_ = Color::Interpolate(Color(201,208,210,128), Color::White, Random::DoubleOnInterval(0.0, 0.4));
    ttl_ = current_tick + Random::IntOnInterval(0, 50000);
    material_ = MaterialType::STEAM;
    up_ = true;
}
    
int Steam::CanMove(Buffer &buffer, int x, int y){
    if(buffer.IsCellEmpty(x, y)){
        return 1;
    }
    else if(buffer.buffer_[x][y].magic_pixel_ptr_->material_ == MaterialType::STEAM){
        return -1;
    }
    return 0;
}

void Steam::CelularAutomata(Buffer &buffer, int x, int y){
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

void Steam::Update(Buffer &buffer, int x, int y){
    CelularAutomata(buffer,x,y);
    up_ = !up_;
}

