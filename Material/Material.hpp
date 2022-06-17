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
#include "Sand.hpp"
#include "Water.hpp"
#include "Rock.hpp"
#include "Gas.hpp"

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
            case MaterialType::GAS:
                return new Gas(index,buffer);
                break;
            default:
                break;
        }
        return new MagicPixel();
    }
};

#endif /* Material_hpp */
