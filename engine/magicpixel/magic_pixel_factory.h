//
//  magic_pixel_factory.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//
#pragma once

#include <map>
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"

class MagicPixelFactory{
public:
    typedef std::unique_ptr<MagicPixel> (*CreateMagicPixelCallback)();
    bool RegisterMagicPixel(MaterialType material, CreateMagicPixelCallback fn);
    std::unique_ptr<MagicPixel> CreateMagicPixel(MaterialType material);
    static MagicPixelFactory* Instance(){
        if(!ptr_instance_)
            ptr_instance_ = new MagicPixelFactory;
        return ptr_instance_;
    }
private:
    std::map<MaterialType,CreateMagicPixelCallback> callback_map;
    MagicPixelFactory() = default;
    MagicPixelFactory(const MagicPixelFactory&);
    MagicPixelFactory& operator=(const MagicPixelFactory&);
    static MagicPixelFactory* ptr_instance_;
};
