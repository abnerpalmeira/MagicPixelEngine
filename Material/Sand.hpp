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

class Sand : public Movable{
private:
    static int movement_priority_[3];
public:
    Sand(int index, std::vector<MagicPixel*> *buffer);
    bool CanMove(int index);
    void Update();
};

#endif /* Sand_hpp */
