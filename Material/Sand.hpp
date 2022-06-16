//
//  Sand.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Sand_hpp
#define Sand_hpp

#include <stdio.h>
#include "MagicPixel.hpp"
#include "Movable.hpp"

class Sand : public Movable{
private:
    int dir_[5] = {Orientation::DOWN,Orientation::DOWN_RIGHT,Orientation::DOWN_LEFT,Orientation::RIGHT,Orientation::LEFT};
public:
    Sand(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        position_ = Helper::GetCords(index);
        buffer_ = buffer;
        Color foo = Color(255,207,92,255);
        color_ = Color::Interpolate(foo, Color::Black, Helper::RandomDoubleOnInterval(0.0, 0.15));
    }
    
    bool CanMove(int index){
        return (*buffer_)[index] == NULL;
    }
    
    void Update(){
        MoveStep(Helper::RandomIntOnInterval(1,3), dir_[0]);
        if(IsUpdated()) return;
        if(Helper::CoinToss()){
            std::swap(dir_[1],dir_[2]);
        }
        MoveStep(1, dir_[1]);
        if(IsUpdated()) return;
        MoveStep(1, dir_[2]);
    }
};

#endif /* Sand_hpp */
