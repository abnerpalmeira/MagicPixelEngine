//
//  Gas.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "Gas.hpp"


Gas::Gas(int index, std::vector<MagicPixel*> *buffer){
    color_ = Color(201,208,210,128);
//    color_ = Color::Interpolate(Color(201,208,210,128), Color::White, Random::DoubleOnInterval(0.0, 0.4));
    ttl_ = current_tick + Random::IntOnInterval(0, 50000);
//    material_ = MaterialType::GAS;
}
    
int Gas::CanMove(int index){
    MagicPixel *current = nullptr;
    if(current == nullptr){
        return 1;
    }
//    else if(current->material_ == MaterialType::GAS){
//        return -1;
//    }
    return 0;
}

void Gas::CelularAutomata(){
//    if(up_){
//        MoveStep(4, Orientation::UP);
//    }else{
//        MoveStep(2, Orientation::DOWN);
//    }
//    up_ = !up_;
////    if(IsUpdated()){
////        return;
////    }
//    if(Random::CoinToss()){
//        MoveStep(1, Orientation::UP_RIGHT);
//        MoveStep(1, Orientation::UP_LEFT);
//    }
//    else{
//        MoveStep(1, Orientation::UP_LEFT);
//        MoveStep(1, Orientation::UP_RIGHT);
//    }
}

void Gas::Update(){
    CelularAutomata();

}
