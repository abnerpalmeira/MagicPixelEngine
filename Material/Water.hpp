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
        return (*buffer_)[index] == NULL;
    }
    
    void CelularAutomata(){
        MoveStep(2, dir_[0]);
        if(IsUpdated()) return;
        if(Helper::CoinToss()) std::swap(dir_[1],dir_[2]);
        MoveStep(1, dir_[1]);
        if(IsUpdated()) return;
        MoveStep(1, dir_[2]);
        if(IsUpdated()) return;
        if(Helper::CoinToss()) std::swap(dir_[3],dir_[4]);
        MoveStep(5, dir_[3]);
        if(IsUpdated()) return;
        MoveStep(5, dir_[4]);
        
        
    }
    void Update(){
        CelularAutomata();
    }
};

#endif /* Water_hpp */
