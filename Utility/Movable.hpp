//
//  Navigation.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Movable_hpp
#define Movable_hpp

#include <stdio.h>
#include <vector>
#include "Global.hpp"
#include "MagicPixel.hpp"
#include "Vector2.hpp"

class Movable : virtual public MagicPixel{
private:
public:
    enum Orientation{
      DOWN,
      UP,
      RIGHT,
      LEFT,
      DOWN_RIGHT,
      DOWN_LEFT,
      UP_RIGHT,
      UP_LEFT,
    };
    int dx_[8] = {0, 0, 1,-1,1,-1, 1,-1};
    int dy_[8] = {1,-1, 0, 0,1, 1,-1,-1};
    virtual bool CanMove(int idx){ return false; }
    Vector2 LineCover(Vector2 target, bool super = false);
    void MoveStep(int step,int direction);
};

#endif /* Navigation_hpp */
