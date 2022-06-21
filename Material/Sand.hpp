//
//  Sand.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Sand_hpp
#define Sand_hpp

#include <stdio.h>
#include "MagicPixel.hpp"
#include "Movable.hpp"
#include "Random.hpp"

class Sand : public Movable{
private:
    void CelularAutomata();
    void PhysicSimulation();
public:
    Sand(int index, std::vector<MagicPixel*> *buffer);
    int CanMove(int index);
    void Update();
};

#endif /* Sand_hpp */
