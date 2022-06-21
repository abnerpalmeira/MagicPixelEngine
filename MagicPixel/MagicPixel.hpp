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
    static void Create(MagicPixel *a, std::vector<MagicPixel*> *buffer){
  
    }
    static void Swap(MagicPixel *a, MagicPixel *b){
        a->UpdateIndex(b->index_);
        b->UpdateIndex(a->index_);
        std::swap(a,b);
    }
    static void Destroy(MagicPixel *a){
        delete a;
        a = nullptr;
    }
    static void Mutate(MagicPixel *a, MaterialType material){
        Destroy(a);
    }
    void Move(int new_index);
    void UpdateIndex(int new_index);
    bool IsUpdated();
    bool die_ = false;
    bool moved_ = true;
    int desinty_;
    int index_;
    Uint32 ttl_;
    Uint32 last_frame_;
    Color color_;
    Vector2 velocity_;
    Vector2 position_;
    MaterialType material_;
    std::vector<MagicPixel*> *buffer_;
};


#endif /* MagicPixel_hpp */
