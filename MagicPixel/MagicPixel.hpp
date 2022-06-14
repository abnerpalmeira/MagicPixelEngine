//
//  MagicPixel.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 01/06/22.
//

#ifndef MagicPixel_hpp
#define MagicPixel_hpp
#include "MaterialType.hpp"
#include "Color.hpp"
#include "Global.hpp"
#include "Fenwick.hpp"
#include "Helper.hpp"
#include "Vector2.hpp"
#include "SDL2/SDL.h"


class MagicPixel{
public:
    int index_;
    Color color_;
    Vector2 velocity_;
    MaterialType material_;
    Uint32 last_frame_;
    std::vector<MagicPixel*> *buffer_;
    MagicPixel(){}
    virtual void Update(){}
};

class Sand : public MagicPixel{
public:
    Sand(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        buffer_ = buffer;
        Color foo = Color(255,207,92,255);
        color_ = Color::Interpolate(foo, Color::Black, Helper::fRand(0.0, 0.15));
    }
    void Update(){
        Vector2 position = Helper::GetCords(index_);
//        if(buffer[index].has_velocity_){
//            Vector2 aux = buffer[index].velocity_;
//            Vector2 target = position + buffer[index].velocity_*delta_time;
//            index = Helper::GetIndex(target.x_, target.y_);
//            return;
//        }
        int dx[] = {0,1,-1,1,-1,1,-1};
        int dy[] = {1,1,1,-1,-1,0,0};
        
        if(Helper::CoinToss()){
            std::swap(dx[1],dx[2]);
        }
        
        int baz = -1,k = 1;
        if(Helper::CoinToss()){
            k = 2;
        }
        
        for(int i=1;i<=k;i++){
            int a = position.x_ + dx[0] * i, b = position.y_ + dy[0] * i;
            if(a < 0 || b < 0 || a >= 512 || b >= 512) continue;
            int foo = Helper::GetIndex(a, b);
            if((*buffer_)[foo] == NULL){
                baz = foo;
                continue;
            }else break;
        }
        
        if(baz != -1){
            (*buffer_)[index_]->last_frame_ = frame_count;
            index_ = baz;
            return;
        }
        
        for(int i=2;i<3;i++){
            int a = position.x_ + dx[i], b = position.y_ + dy[i];
            if(a < 0 || b < 0 || a >= 512 || b >= 512) continue;
            int foo = Helper::GetIndex(a, b);
            if((*buffer_)[foo] == NULL){
                (*buffer_)[index_]->last_frame_ = frame_count;
                index_ = foo;
                return;
            }
        }
    }
};

class Water : public MagicPixel{
    int dispersion_rate_ = 5;
public:
    Water(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        buffer_ = buffer;
        color_ = Color(131,215,238,180);
    }
    void CelularAutomata(){
        Vector2 position = Helper::GetCords(index_);
        int dx[5] = {0,1,-1,-1,1};
        int dy[5] = {1,1,1,0,0};
        
        if(Helper::CoinToss()){
            std::swap(dx[1],dx[2]);
        }
        if(Helper::CoinToss()){
            std::swap(dx[3],dx[4]);
        }
        
        
        for(int i=0;i<3;i++){
            int a = position.x_ + dx[i], b = position.y_ + dy[i];
            if(a < 0 || b < 0 || a >= 512 || b >= 512) continue;
            int foo = Helper::GetIndex(a, b);
            if((*buffer_)[foo] == NULL){
                (*buffer_)[index_]->last_frame_ = frame_count;
                index_ = foo;
                return;
            }
        }
        
        for(int i=3;i<5;i++){
            int foo = -1;
            for(int j=1;j<=dispersion_rate_;j++){
                int a = position.x_ + dx[i]*j, b = position.y_ + dy[i]*j;
                if(a < 0 || b < 0 || a >= 512 || b >= 512) break;
                int bar = Helper::GetIndex(a, b);
                if((*buffer_)[bar] == NULL) foo = bar;
            }
            if(foo != -1){
                (*buffer_)[index_]->last_frame_ = frame_count;
                index_ = foo;
                return;
            }
        }
    }
    void Update(){
        CelularAutomata();
    }
};

class Rock : public MagicPixel{
public:
    Rock(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        buffer_ = buffer;
        color_ = Color(58,50,50,255);
        if(Helper::CoinToss()) color_ = Color::Interpolate(color_, Color::White, Helper::fRand(0.0, 0.15));
    }
    void Update(){
 
    }
};

#endif /* MagicPixel_hpp */
//0 1 2
//3 4 5
//(0,0) = 0
//(1,0) = 1
//(2,0) = 2
//(0,1) = 3
