//
//  fire.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#include "fire.h"

Color Fire::colors[3] = {Color(215, 53, 2,255),Color(252, 100, 0,255),Color(250, 192, 0,255)};
Uint32 Fire::min_temperature = 250;
Uint32 Fire::max_temperature = 500;
Uint32 Fire::default_ttl = 100;

Fire::Fire(){
    ttl_ = current_tick + default_ttl + Random::IntOnInterval(0, 20);
    material_ = MaterialType::FIRE;
    temperature_ = min_temperature;
    color_ = Color::Interpolate(colors[0], colors[2], Helper::RandomDoubleOnInterval(0.0, 1));
}

void Fire::Update(Buffer &buffer, int x, int y){
    temperature_ = std::min(temperature_+2,max_temperature);
    for(int i=0;i<8;i++){
        int a = x + Navigation::dx[i], b = y + Navigation::dy[i];
        if(a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        if(buffer.buffer_[a][b].Empty()){
            int should_emit = Random::IntOnInterval(0,10);
            if(should_emit <= 1){
                buffer.buffer_[a][b].CreateMagicPixel(MaterialType::GAS);
                buffer.buffer_[a][b].magic_pixel_ptr_->color_ = color_;
                buffer.buffer_[a][b].magic_pixel_ptr_->ttl_ = current_tick + 20;
            }
            else if(should_emit == 3){
                buffer.buffer_[a][b].CreateMagicPixel(MaterialType::GAS);
                buffer.buffer_[a][b].magic_pixel_ptr_->ttl_ = current_tick + 100;
            }
        }
        else if(buffer.buffer_[a][b].GetMaterial() != MaterialType::FIRE){
            buffer.buffer_[a][b].TransferHeat(temperature_);
            buffer.buffer_[a][b].Burn(MaterialType::FIRE,default_ttl);
        }
    }
    if(!Random::IntOnInterval(0, 3)){
        color_ = Color::Interpolate(colors[0], colors[2], Helper::RandomDoubleOnInterval(0.0, 1));
    }
    buffer.buffer_[x][y].SetUpdateFlag();
}
