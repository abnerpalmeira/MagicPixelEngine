//
//  Gas.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Gas_hpp
#define Gas_hpp

#include <stdio.h>
#include "MagicPixel.hpp"
#include "Movable.hpp"

class Gas : public Movable{
private:
    int dir_[5] = {Orientation::UP,Orientation::UP_RIGHT,Orientation::UP_LEFT,Orientation::RIGHT,Orientation::LEFT};

public:
    Gas(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        position_ = Helper::GetCords(index);
        buffer_ = buffer;
        color_ = Color(201,208,210,128);
//        color_ = Color::Interpolate(foo, Color::Black, Helper::RandomDoubleOnInterval(0.0, 0.15));
    }
    
    bool CanMove(int index){
        return (*buffer_)[index] == nullptr;
    }
    
    void Update(){
        MoveStep(1, dir_[0]);
        if(Helper::CoinToss()){
            std::swap(dir_[1],dir_[2]);
        }
        MoveStep(1, dir_[1]);
        if(IsUpdated()) return;
        MoveStep(1, dir_[2]);
    }
};

#endif /* Gas_hpp */
