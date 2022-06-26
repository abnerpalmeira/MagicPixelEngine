//
//  Water.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//

#include "Water.hpp"

Water::Water(){
    color_ = Color(131,215,238,180);
    velocity_ = Vector2(0,0);
    material_ = MaterialType::WATER;
}

int Water::CanMove(Buffer &buffer, int x, int y){
    return buffer.IsCellEmpty(x, y);
}

void Water::CelularAutomata(Buffer &buffer,int x,int y){
    if(MoveStep(buffer,Random::IntOnInterval(1, 3), Orientation::DOWN,x,y)) return;
    if(Random::CoinToss()){
        if(MoveStep(buffer,1, Orientation::DOWN_RIGHT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::DOWN_LEFT,x,y)) return;
    }
    else{
        if(MoveStep(buffer,1, Orientation::DOWN_LEFT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::DOWN_RIGHT,x,y)) return;
    }
    if(Random::CoinToss()){
        if(MoveStep(buffer,1, Orientation::RIGHT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::LEFT,x,y)) return;
    }
    else{
        if(MoveStep(buffer,1, Orientation::LEFT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::RIGHT,x,y)) return;
    }
}

void Water::Update(Buffer &buffer,int x,int y){
    if(velocity_.x_ == 0 && velocity_.y_ == 0){
        CelularAutomata(buffer,x,y);
    }
    else{
//        PhysicSimulation();
    }
}
