//
//  Fire.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 26/06/22.
//

#include "Fire.h"

Color Fire::colors[3] = {Color(215, 53, 2,255),Color(252, 100, 0,255),Color(250, 192, 0,255)};
Uint32 Fire::min_temperature = 250;
Uint32 Fire::max_temperature = 500;
Uint32 Fire::default_ttl = 100;

Fire::Fire(){
    color_ = colors[0];
    ttl_ = current_tick + default_ttl + Random::IntOnInterval(0, 20);
    material_ = MaterialType::FIRE;
    temperature_ = min_temperature;
    if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Helper::RandomDoubleOnInterval(0.0, 0.2));
}

void Fire::Update(Buffer &buffer, int x, int y){
    temperature_ = std::min(temperature_+2,max_temperature);
    for(int i=0;i<8;i++){
        int a = x + Navigation::dx[i], b = y + Navigation::dy[i];
        if(a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        if(!buffer.buffer_[a][b].Empty() && buffer.buffer_[a][b].GetMaterial() != MaterialType::FIRE){
            buffer.buffer_[a][b].TransferHeat(temperature_);
            buffer.buffer_[a][b].Burn(MaterialType::FIRE,default_ttl);
        }
    }
    if(temperature_ <= 300) color_ = colors[0];
    else if(temperature_ <= 450) color_ = colors[1];
    else color_ = colors[2];
    color_ = Color::Interpolate(color_, Color::White, Helper::RandomDoubleOnInterval(0.0, 0.2));
}
