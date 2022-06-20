//
//  Gas.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Gas_hpp
#define Gas_hpp

#include <stdio.h>
#include "MagicPixel.hpp"
#include "Movable.hpp"
#include "Random.hpp"


class Gas : public Movable{
private:
    bool up_ = true;
public:
    Gas(int index, std::vector<MagicPixel*> *buffer);
    void CelularAutomata();
    virtual ~Gas(){}
    bool CanMove(int index);
    void Update();
};

#endif /* Gas_hpp */
