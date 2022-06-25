//
//  Cell.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#include "Cell.hpp"
#include "Buffer.hpp"

bool Cell::Empty(){
    return magic_pixel_ptr_ == nullptr;
}

void Cell::Update(Buffer &buffer){
    update_ = false;
    if(magic_pixel_ptr_ == nullptr) return;
    magic_pixel_ptr_->Update(buffer,x_,y_);
}

void Cell::SetUpdateFlag(){
    update_ = true;
}
