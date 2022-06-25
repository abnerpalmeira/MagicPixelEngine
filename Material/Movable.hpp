//
//  Navigation.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#pragma once

#include <stdio.h>
#include <vector>
#include "Buffer.hpp"
#include "Global.hpp"
#include "MagicPixel.hpp"
#include "Vector2.hpp"

class Movable : virtual public MagicPixel{
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
    virtual int CanMove(Buffer &buffer, int x, int y){ return false; }
    bool MoveStep(Buffer &buffer,int step,int direction,int x,int y);
    bool LineCover(Buffer &buffer, Vector2 target,int x, int y, bool super = false);
    int dx_[8] = {0, 0, 1,-1,1,-1, 1,-1};
    int dy_[8] = {1,-1, 0, 0,1, 1,-1,-1};
private:
};
