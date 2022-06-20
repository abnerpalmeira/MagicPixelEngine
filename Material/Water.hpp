//
//  Water.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Water_hpp
#define Water_hpp

#include <stdio.h>
#include "MagicPixel.hpp"

class Water : public Movable{
    int dir_[5] = {Orientation::DOWN,Orientation::DOWN_RIGHT,Orientation::DOWN_LEFT,Orientation::RIGHT,Orientation::LEFT};
public:
    Water(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        position_ = Helper::GetCords(index);
        buffer_ = buffer;
        color_ = Color(131,215,238,180);
    }
    
    bool CanMove(int index){
        return (*buffer_)[index] == nullptr;
    }
    
    void CelularAutomata(){
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
    
    void Update(){
        CelularAutomata();
    }
};

#endif /* Water_hpp */
