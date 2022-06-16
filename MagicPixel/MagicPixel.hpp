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
    virtual ~MagicPixel(){}
    virtual void Update(){}
    void UpdateBuffer(int new_index){
        std::swap((*buffer_)[index_],(*buffer_)[new_index]);
    }
    void UpdateIndex(int new_index){
        UpdateBuffer(new_index);
        index_ = new_index;
        position_ = Helper::GetCords(new_index);
    }
    bool IsUpdated(){
        return last_frame_ == frame_count;
    }
};


#endif /* MagicPixel_hpp */
