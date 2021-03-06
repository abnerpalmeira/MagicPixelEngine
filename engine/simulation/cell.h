//
//  cell.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#pragma once

#include <memory>
#include "magicpixel/magic_pixel.h"
#include "magicpixel/magic_pixel_factory.h"
#include  "common/utility/random.h"

class Buffer;
class Cell{
public:
    Cell() = default;
    bool Empty();
    void PreUpdate();
    void SetUpdateFlag();
    void Update(Buffer &buffer);
    void TransferHeat(int temperature);
    void CreateMagicPixel(MaterialType material);
    void ReplacMagicPixel(MaterialType material);
    void RemoveMagicPixel();
    MaterialType GetMaterial();
    void Burn(MaterialType material, int base_ttl);
    std::unique_ptr<MagicPixel> magic_pixel_ptr_;
    bool update_;
    int x_,y_;
};
