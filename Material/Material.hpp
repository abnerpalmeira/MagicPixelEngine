//
//  Material.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 02/06/22.
//
#pragma once
#ifndef Material_hpp
#define Material_hpp
#include <tuple>
#include <stdio.h>
#include <vector>
#include <string>
#include "SDL2/SDL.h"
#include "Color.hpp"
#include "MaterialType.hpp"
#include "MagicPixel.hpp"


class Material{
public:
    static MagicPixel* Init(int index, MaterialType material, std::vector<MagicPixel*> *buffer){
        switch (material) {
            case MaterialType::SAND:
                return new Sand(index,buffer);
                break;
            case MaterialType::WATER:
                return new Water(index,buffer);
                break;
            case MaterialType::ROCK:
                return new Rock(index,buffer);
                break;
            default:
                break;
        }
        return new MagicPixel();
    }
};

//const std::vector<Material> materials = {
//    Material(MaterialType::EMPTY,"Empty", Color(0, 0, 0,0)),
//    Material(MaterialType::ROCK,"Rock", Color(58,50,50,255)),
//    Material(MaterialType::SAND,"Sand",Color(255,207,92,255)),
//    Material(MaterialType::WATER,"Water",Color(35,137,218,255)),
//    Material(MaterialType::FIRE,"Fire",Color(250,77,10,255)),
//    Material(MaterialType::LAVA,"Lava",Color(207,16,32,255)),
//    Material(MaterialType::OIL,"Oil",Color(58,50,50,255)),
//    Material(MaterialType::ICE,"Ice",Color(58,50,50,255)),
//    Material(MaterialType::GAS,"Gas",Color(58,50,50,255)),
//    Material(MaterialType::STEAM,"Steam",Color(58,50,50,255)),
//    Material(MaterialType::WOOD,"Wood",Color(58,50,50,255)),
//    Material(MaterialType::PLASMA,"Plasma",Color(58,50,50,255)),
//};


#endif /* Material_hpp */
