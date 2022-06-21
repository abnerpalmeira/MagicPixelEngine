//
//  Water.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Water_hpp
#define Water_hpp

#include <stdio.h>
#include "MagicPixel.hpp"
#include "Movable.hpp"
#include "Random.hpp"

class Water : public Movable{
public:
    Water(int index, std::vector<MagicPixel*> *buffer);
    int CanMove(int index);
    void CelularAutomata();
    void Update();
};

#endif /* Water_hpp */
