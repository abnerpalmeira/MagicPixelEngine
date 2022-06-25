//
//  Buffer.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#include "Buffer.hpp"

Buffer::Buffer(){
    for(int i=0;i<buffer_.size();i++){
        for(int j=0;j<buffer_[i].size();j++){
            buffer_[i][j].x_ = i;
            buffer_[i][j].y_ = j;
            buffer_[i][j].update_ = false;
        }
    }
}


Uint32 Buffer::GetCellColor(int x,int y){
    return IsCellEmpty(x,y) ? kEmptyPixelValue:buffer_[x][y].magic_pixel_ptr_->color_.GetSDLMap();
}


bool Buffer::IsCellEmpty(int x,int y){
    return buffer_[x][y].magic_pixel_ptr_ == nullptr;
}

void Buffer::CreateMagicPixel(MaterialType material,int x,int y){
    buffer_[x][y].magic_pixel_ptr_ = MagicPixelFactory::Instance()->CreateMagicPixel(material);
    buffer_[x][y].update_ = true;
}

void Buffer::RemoveMagicPixel(int x,int y){
    buffer_[x][y].magic_pixel_ptr_.reset();
    buffer_[x][y].update_ = true;
}

void Buffer::SwapCell(int x,int y,int a ,int b){
}

void Buffer::MoveCell(int x,int y,int a ,int b){
    if(!IsCellEmpty(a, b)){
        SwapCell(x,y,a,b);
    }
    else{
        buffer_[a][b].magic_pixel_ptr_ = std::move(buffer_[x][y].magic_pixel_ptr_);
        buffer_[x][y].update_ = true;
        buffer_[a][b].update_ = true;
    }
}
