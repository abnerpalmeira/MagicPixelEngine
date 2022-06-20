//
//  Gas.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "Gas.hpp"


Gas::Gas(int index, std::vector<MagicPixel*> *buffer){
    index_ = index;
    position_ = Helper::GetCords(index);
    buffer_ = buffer;
    color_ = Color::Interpolate(Color(201,208,210,128), Color::White, Random::DoubleOnInterval(0.0, 0.4));
    ttl_ = current_tick + Random::IntOnInterval(0, 50000);
    material_ = MaterialType::GAS;
}
    
bool Gas::CanMove(int index){
    return (*buffer_)[index] == nullptr;
}

void Gas::CelularAutomata(){
    if(up_){
        MoveStep(10, Orientation::UP);
    }else{
        MoveStep(1, Orientation::DOWN);
    }
    up_ = !up_;
    if(IsUpdated()){
        return;
    }
    if(Random::CoinToss()){
        MoveStep(2, Orientation::UP_RIGHT);
        MoveStep(2, Orientation::UP_LEFT);
    }
    else{
        MoveStep(2, Orientation::UP_LEFT);
        MoveStep(2, Orientation::UP_RIGHT);
    }
}

void Gas::Update(){
    CelularAutomata();

}
