//
//  Water.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Water_hpp
#define Water_hpp

#include <stdio.h>
#include "MagicPixel.hpp"

class Water : public MagicPixel{
    int dispersion_rate_ = 5;
public:
    Water(int index, std::vector<MagicPixel*> *buffer){
        index_ = index;
        buffer_ = buffer;
        color_ = Color(131,215,238,180);
    }
    
    bool CanMove(int idx){
        return true;
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

#endif /* Water_hpp */
