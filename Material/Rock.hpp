//
//  Rock.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Rock_hpp
#define Rock_hpp

#include <stdio.h>
#include "MagicPixel.hpp"

class Rock : public MagicPixel{
public:
    Rock(int index, std::vector<MagicPixel*> *buffer);
    void Update();
    bool CanMove(int idx);
};


#endif /* Rock_hpp */
