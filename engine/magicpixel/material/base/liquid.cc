//
//  liquid.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#include "liquid.h"

Liquid::Liquid(){
    color_ = Color(128,128,128,180);
    material_ = MaterialType::LIQUID;
    dispersion_rate_ = 1;
}

int Liquid::CanMove(Buffer &buffer, int x, int y){
    return buffer.IsCellEmpty(x, y);
}

void Liquid::CelularAutomata(Buffer &buffer,int x,int y){
    if(MoveStep(buffer,Random::IntOnInterval(1, 3), Orientation::DOWN,x,y)) return;
    if(Random::CoinToss()){
        if(MoveStep(buffer,1, Orientation::DOWN_RIGHT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::DOWN_LEFT,x,y)) return;
    }
    else{
        if(MoveStep(buffer,1, Orientation::DOWN_LEFT,x,y)) return;
        if(MoveStep(buffer,1, Orientation::DOWN_RIGHT,x,y)) return;
    }
    if(Random::CoinToss()){
        if(MoveStep(buffer,dispersion_rate_, Orientation::RIGHT,x,y)) return;
        if(MoveStep(buffer,dispersion_rate_, Orientation::LEFT,x,y)) return;
    }
    else{
        if(MoveStep(buffer,dispersion_rate_, Orientation::LEFT,x,y)) return;
        if(MoveStep(buffer,dispersion_rate_, Orientation::RIGHT,x,y)) return;
    }
}

void Liquid::Update(Buffer &buffer,int x,int y){
    CelularAutomata(buffer,x,y);
}
