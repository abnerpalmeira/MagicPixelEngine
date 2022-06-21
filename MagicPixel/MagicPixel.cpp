//
//  MagicPixel.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 21/06/22.
//
#include "MagicPixel.hpp"

    MagicPixel::MagicPixel(){}
    void MagicPixel::UpdateIndex(int new_index){
        index_ = new_index;
        position_ = Helper::GetCords(new_index);
    }
    bool MagicPixel::IsUpdated(){
        return last_frame_ == frame_count;
    }
    void Move(int new_index){
        
    }
    void UpdateIndex(int new_index){
        
    }

