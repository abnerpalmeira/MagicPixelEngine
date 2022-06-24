//
//  Sand.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#include "Sand.hpp"

Sand::Sand(){
    color_ = Color::Interpolate(Color(255,207,92,255), Color::Black, Random::DoubleOnInterval(0.0, 0.15));
    velocity_ = Vector2(0,0);
}

int Sand::CanMove(int index){
    return 0;
}

void Sand::CelularAutomata(){
    MoveStep(Random::IntOnInterval(1, 3), Orientation::DOWN);
    if(IsUpdated()) return;
    if(Random::CoinToss()){
        MoveStep(1, Orientation::DOWN_RIGHT);
        MoveStep(1, Orientation::DOWN_LEFT);
    }
    else{
        MoveStep(1, Orientation::DOWN_LEFT);
        MoveStep(1, Orientation::DOWN_RIGHT);
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
