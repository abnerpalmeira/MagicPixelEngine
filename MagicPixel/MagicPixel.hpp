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
    MagicPixel();
    virtual ~MagicPixel(){}
    virtual void Update(){}
    virtual void ApplyEffects(){}
   
    void Move(int new_index);
    void UpdateIndex(int new_index);
    bool IsUpdated();
    bool die_ = false;

    int desinty_;
    int index_;
    Uint32 ttl_;
    Uint32 last_frame_;
    Color color_;
    Vector2 velocity_;
    Vector2 position_;
    MaterialType material_;
};


#endif /* MagicPixel_hpp */
