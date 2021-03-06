//
//  cell.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 23/06/22.
//

#include "simulation/buffer.h"
#include "cell.h"

bool Cell::Empty(){
    return magic_pixel_ptr_ == nullptr;
}

void Cell::PreUpdate(){
    if(Empty()) return;
    if(magic_pixel_ptr_->ttl_ && magic_pixel_ptr_->ttl_ <= current_tick){
        
    }
}

void Cell::Update(Buffer &buffer){
    update_ = false;
    if(magic_pixel_ptr_ == nullptr) return;
    magic_pixel_ptr_->Update(buffer,x_,y_);
}

void Cell::SetUpdateFlag(){
    update_ = true;
}

void Cell::TransferHeat(int temperature){
    magic_pixel_ptr_->temperature_ += (int)(temperature * Random::DoubleOnInterval(0.01, 0.02));
}

void Cell::CreateMagicPixel(MaterialType material){
    magic_pixel_ptr_ = MagicPixelFactory::Instance()->CreateMagicPixel(material);
    update_ = true;
}

void Cell::ReplacMagicPixel(MaterialType material){
    RemoveMagicPixel();
    CreateMagicPixel(material);
}

void Cell::RemoveMagicPixel(){
    magic_pixel_ptr_.reset();
    update_ = true;
}

MaterialType Cell::GetMaterial(){
    if(magic_pixel_ptr_ == nullptr) return MaterialType::EMPTY;
    return magic_pixel_ptr_->material_;
}

void Cell::Burn(MaterialType material, int base_ttl){
    if(magic_pixel_ptr_->ignite_temperature_ && magic_pixel_ptr_->ignite_temperature_ <= magic_pixel_ptr_->temperature_){
        Uint32 surface_area = magic_pixel_ptr_->surface_area_;
        ReplacMagicPixel(material);
        magic_pixel_ptr_->ttl_ = current_tick + base_ttl*surface_area + Random::IntOnInterval(0, 1000);
    }
}
