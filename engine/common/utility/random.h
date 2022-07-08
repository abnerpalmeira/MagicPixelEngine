//
//  random.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#pragma once

#include <utility>
#include "core/global.h"

class Random{
public:
    static double DoubleOnInterval(double min, double max){
        return std::uniform_real_distribution<double>(min, max )(rng);
    }
    
    static int IntOnInterval(int min, int max){
        return std::uniform_int_distribution<int>(min, max)(rng);
    }
    
    static bool CoinToss(){
        return std::uniform_int_distribution<int>(0, 1)(rng);
    }
};
