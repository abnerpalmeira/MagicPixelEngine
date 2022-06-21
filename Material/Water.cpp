//
//  Water.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//

#include "Water.hpp"

Water::Water(int index, std::vector<MagicPixel*> *buffer){
    index_ = index;
    position_ = Helper::GetCords(index);
    buffer_ = buffer;
    color_ = Color(131,215,238,180);
}

int Water::CanMove(int index){
    return (int)((*buffer_)[index] == nullptr);
}

void Water::CelularAutomata(){
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
    if(IsUpdated()) return;
    if(Random::CoinToss()){
        MoveStep(1,Orientation::RIGHT);
        if(IsUpdated()) return;
        MoveStep(1,Orientation::LEFT);
    }
    else{
        MoveStep(1,Orientation::LEFT);
        if(IsUpdated()) return;
        MoveStep(1,Orientation::RIGHT);
    }
}

void Water::Update(){
    CelularAutomata();
}
