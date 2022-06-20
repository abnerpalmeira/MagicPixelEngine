//
//  Sand.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "Sand.hpp"

int Sand::movement_priority_[3] = {Orientation::DOWN,Orientation::DOWN_RIGHT,Orientation::DOWN_LEFT};

Sand::Sand(int index, std::vector<MagicPixel*> *buffer){
    index_ = index;
    position_ = Helper::GetCords(index);
    buffer_ = buffer;
    color_ = Color::Interpolate(Color(255,207,92,255), Color::Black, Random::DoubleOnInterval(0.0, 0.15));
    velocity_ = Vector2(0,0);
}

bool Sand::CanMove(int index){
    return (*buffer_)[index] == nullptr;
}

void Sand::CelularAutomata(){
    MoveStep(Random::IntOnInterval(1, 3), movement_priority_[0]);
    if(IsUpdated()) return;
    if(Random::CoinToss()){
        MoveStep(1, movement_priority_[1]);
        MoveStep(1, movement_priority_[2]);
    }
    else{
        MoveStep(1, movement_priority_[2]);
        MoveStep(1, movement_priority_[1]);
    }
}

void Sand::PhysicSimulation(){
    Vector2 target = position_+Vector2(ceil(velocity_.x_*delta_time),ceil(velocity_.y_*delta_time));
    Vector2 next_position = LineCover(target);
    position_ = next_position;
    if(target != next_position){
        velocity_ = Vector2(0,0);
    }
    
}

void Sand::Update(){
    if(velocity_.x_ == 0 && velocity_.y_ == 0){
        CelularAutomata();
    }
    else{
        PhysicSimulation();
    }
}
