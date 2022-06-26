//
//  Random.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#ifndef Random_hpp
#define Random_hpp

#include <stdio.h>
#include <utility>
#include "Global.hpp"

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

#endif /* Random_hpp */
