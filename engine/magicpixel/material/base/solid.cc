//
//  solid.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "magicpixel/material/base/solid.h"

Solid::Solid(){
    color_ = Color::Interpolate(Color(128,128,128,255), Color::Black, Random::DoubleOnInterval(0.0, 0.15));
    velocity_ = Vector2(0,0);
    material_ = MaterialType::SOLID;
}

int Solid::CanMove(Buffer &buffer, int x, int y){
    return buffer.IsCellEmpty(x, y);
}

void Solid::CelularAutomata(Buffer &buffer,int x,int y){
    if(MoveStep(buffer,Random::IntOnInterval(1, 3), Orientation::DOWN,x,y)) return;
    if(Random::CoinToss()){
        if(MoveStep(buffer,1, Orientation::DOWN_RIGHT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::DOWN_LEFT,x,y)) return;
    }
    else{
        if(MoveStep(buffer,1, Orientation::DOWN_LEFT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::DOWN_RIGHT,x,y)) return;
    }
}

void Solid::PhysicSimulation(){
}

void Solid::Update(Buffer &buffer,int x,int y){
    if(velocity_.x_ == 0 && velocity_.y_ == 0){
        CelularAutomata(buffer,x,y);
    }
    else{
        PhysicSimulation();
    }
}
