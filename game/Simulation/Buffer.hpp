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
#include "MaterialType.hpp"

class Buffer{
public:
    Buffer();
    Uint32 GetCellColor(int x,int y);
    MaterialType GetMaterial(int x,int y);
    bool IsCellEmpty(int x,int y);
    bool IsExpired(int x,int y);
    bool Ignites(int x,int y, int temperature);
    void CreateMagicPixel(MaterialType material,int x,int y);
    void ReplacMagicPixel(MaterialType material,int x,int y);
    void SetTemperature(int x,int y,int temperature);
    void RemoveMagicPixel(int x,int y);
    void SwapCell(int x,int y,int a ,int b);
    void MoveCell(int x,int y,int a ,int b);
    void Reset();
    std::array<std::array<Cell,kSimulationHeight>,kSimulationWidth> buffer_;
private:
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
