//
//  MagicPixel.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 01/06/22.
//

#ifndef MagicPixel_hpp
#define MagicPixel_hpp
#include "MaterialType.hpp"
#include "Color.hpp"
#include "Global.hpp"
#include "Fenwick.hpp"
#include "Helper.hpp"
#include "Vector2.hpp"
#include "SDL2/SDL.h"


class MagicPixel{
public:
    int index_;
    Uint32 last_frame_;
    Color color_;
    Vector2 velocity_;
    Vector2 position_;
    MaterialType material_;
    std::vector<MagicPixel*> *buffer_;
    MagicPixel(){}
    virtual void Update(){}
    void UpdatePosition(Vector2 position){
        position_ = position;
        index_ = Helper::GetIndex(position.x_, position_.y_);
    }
    void UpdateIndex(int index){
        index_ = index;
        position_ = Helper::GetCords(index);
    }
    bool IsUpdated(){
        return last_frame_ == frame_count;
    }
};


#endif /* MagicPixel_hpp */
