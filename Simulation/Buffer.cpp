//
//  Buffer.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#include "Buffer.hpp"

bool Buffer::IsCellEmpty(int x,int y){
    return buffer_[Helper::GetIndex(x, y)].magic_pixel_ptr_ == nullptr;
}

bool Buffer::IsCellEmpty(int index){
    return buffer_[index].magic_pixel_ptr_ == nullptr;
}

void Buffer::CreateMagicPixel(MaterialType material,int x,int y){
    buffer_[Helper::GetIndex(x, y)].magic_pixel_ptr_ = MagicPixelFactory::Instance()->CreateMagicPixel(material);
}

Uint32 Buffer::GetCellColor(int x,int y){
    int index = Helper::GetIndex(x, y);
    return IsCellEmpty(index) ? kEmptyPixelValue:buffer_[Helper::GetIndex(x, y)].magic_pixel_ptr_->color_.GetSDLMap();
}
