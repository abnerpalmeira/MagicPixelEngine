//
//  Cell.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#pragma once

#include <memory>
#include "MagicPixel.hpp"
#include "MagicPixelFactory.hpp"

class Cell{
public:
    Cell() = default;
    void CreateMagicPixel(MaterialType material);
    bool Empty();
    std::unique_ptr<MagicPixel> magic_pixel_ptr_;
    Uint32 ttl_;
    int x_,y_;
    int index_;
    bool moved_;
    bool die_;
    
};
