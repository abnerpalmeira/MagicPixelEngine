//
//  Fire.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#include "Fire.h"
//ABGR
Color Fire::color_array[3] = {Color(215, 53, 2,255),Color(252, 100, 0,255),Color(250, 192, 0,255)};
//Color Fire::color_array[3] = {Color(215, 53, 2,255),Color(252, 100, 0,255),Color(250, 192, 0,255)};
//Color Fire::color_array[3] = {Color(255,2, 53, 215),Color(255,0, 100, 252),Color(255,0, 192, 250)};

Fire::Fire(){
    color_ = color_array[Random::IntOnInterval(0, 2)];
    ttl_ = current_tick + Random::IntOnInterval(0, 100);
    material_ = MaterialType::FIRE;
    temperature_ = 250;
}

void Fire::Update(Buffer &buffer, int x, int y){
    temperature_ = std::min((int)temperature_+20,500);
    int dx_[8] = {0, 0, 1,-1,1,-1, 1,-1};
    int dy_[8] = {1,-1, 0, 0,1, 1,-1,-1};
    for(int i=0;i<8;i++){
        int a = x + dx_[i], b = y + dy_[i];
        if(a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        if(buffer.Ignites(a, b, temperature_)){
            buffer.ReplacMagicPixel(MaterialType::FIRE,a,b);
            buffer.buffer_[x][y].magic_pixel_ptr_->temperature_ = 1;
            buffer.buffer_[x][y].magic_pixel_ptr_->ttl_ = current_tick + Random::IntOnInterval(1000, 2500);
        }
    }
    color_ = color_array[Random::IntOnInterval(0, 2)];
}
