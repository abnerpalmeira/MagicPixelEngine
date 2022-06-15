//
//  Rock.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Rock_hpp
#define Rock_hpp

#include <stdio.h>
#include "MagicPixel.hpp"

class Rock : public MagicPixel{
public:
    Rock(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        buffer_ = buffer;
        color_ = Color(58,50,50,255);
        if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Helper::fRand(0.0, 0.15));
    }
    void Update(){
 
    }
    
    bool CanMove(int idx){
        return true;
    }
};


#endif /* Rock_hpp */
