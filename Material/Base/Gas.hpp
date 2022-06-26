//
//  Gas.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include "MagicPixel.hpp"
#include "Movable.hpp"
#include "Random.h"


class Gas : public Movable{
private:
    bool up_ = true;
public:
    Gas(int index, std::vector<MagicPixel*> *buffer);
    void CelularAutomata();
    virtual ~Gas(){}
    int CanMove(int index);
    void Update();
};

