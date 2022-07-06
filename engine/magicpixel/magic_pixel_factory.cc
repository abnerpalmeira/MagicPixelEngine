//
//  magic_pixel_factory.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#include "magic_pixel_factory.h"

MagicPixelFactory* MagicPixelFactory::ptr_instance_ = nullptr;

bool MagicPixelFactory::RegisterMagicPixel(MaterialType material, CreateMagicPixelCallback fn){
    callback_map[material] = fn;
    return true;
}
std::unique_ptr<MagicPixel> MagicPixelFactory::CreateMagicPixel(MaterialType material){
    return callback_map[material]();
}
