//
//  Buffer.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#pragma once

#include <array>
#include "Cell.hpp"
#include "MagicPixelFactory.hpp"

class Buffer{
public:
    bool IsCellEmpty(int x,int y);
    bool IsCellEmpty(int index);
    void CreateMagicPixel(MaterialType material,int x,int y);
    Uint32 GetCellColor(int x,int y);
private:
    std::array<Cell,kMaxCell> buffer_;
    

//    static void Create(){
//  
//    }
//    static void Swap(MagicPixel *a, MagicPixel *b){
//        a->UpdateIndex(b->index_);
//        b->UpdateIndex(a->index_);
//        std::swap(a,b);
//    }
//    static void Destroy(MagicPixel *a){
//        delete a;
//        a = nullptr;
//    }
//    static void Mutate(MagicPixel *a, MaterialType material){
//        Destroy(a);
//    }
};
