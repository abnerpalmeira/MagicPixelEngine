//
//  Gas.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "Gas.hpp"

int Gas::movement_priority_[3] = {Orientation::UP,Orientation::UP_RIGHT,Orientation::UP_LEFT};


Gas::Gas(int index, std::vector<MagicPixel*> *buffer){
    index_ = index;
    position_ = Helper::GetCords(index);
    buffer_ = buffer;
    color_ = Color::Interpolate(Color(201,208,210,128), Color::White, Random::DoubleOnInterval(0.0, 0.4));
}
    
bool Gas::CanMove(int index){
    return (*buffer_)[index] == nullptr;
}

void Gas::Update(){
    MoveStep(1, movement_priority_[0]);
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
