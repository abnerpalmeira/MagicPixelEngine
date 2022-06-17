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
    color_ = Color::Interpolate(Color(255,207,92,255), Color::Black, Helper::RandomDoubleOnInterval(0.0, 0.15));
}

bool Sand::CanMove(int index){
    return (*buffer_)[index] == nullptr;
}

void Sand::Update(){
    int *first,*second;
    MoveStep(Helper::RandomIntOnInterval(1,3), movement_priority_[0]);
    goto HEAVEN;
    if(IsUpdated()) return;
    if(!IsUpdated() && Helper::CoinToss()){
        first = &
    }
    if(IsUpdated()) return;
    if(Helper::CoinToss()){
        std::swap(movement_priority_[1],movement_priority_[2]);
    }
    MoveStep(1, movement_priority_[1]);
    if(IsUpdated()) return;
    MoveStep(1, movement_priority_[2]);
    HEAVEN:
    return;
}
