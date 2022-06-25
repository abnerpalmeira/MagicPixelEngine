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

class Buffer;
class Cell{
public:
    Cell() = default;
    bool Empty();
    void Update(Buffer &buffer);
    void CreateMagicPixel(MaterialType material);
    void SetUpdateFlag();
    std::unique_ptr<MagicPixel> magic_pixel_ptr_;
    bool update_;
    int x_,y_;
};
