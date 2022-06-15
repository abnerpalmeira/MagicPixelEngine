//
//  Sand.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//

#ifndef Sand_hpp
#define Sand_hpp

#include <stdio.h>
#include "MagicPixel.hpp"
#include "Movable.hpp"

class Sand : public Movable{
private:
    int dir[5] = {Orientation::DOWN,Orientation::DOWN_RIGHT,Orientation::DOWN_LEFT,Orientation::RIGHT,Orientation::LEFT};
public:
    Sand(int index, std::vector<MagicPixel*> *buffer){
        UpdateIndex(index);
        buffer_ = buffer;
        Color foo = Color(255,207,92,255);
        color_ = Color::Interpolate(foo, Color::Black, Helper::fRand(0.0, 0.15));
    }
    
    bool CanMove(int index){
        return (*buffer_)[index] == NULL;
    }
    
    void Update(){
        Vector2 position = Helper::GetCords(index_);
        MoveStep(1, dir[0]);
       
        
//        if(Helper::CoinToss()){
//            std::swap(dx[1],dx[2]);
//        }
//
//        int baz = -1,k = 1;
//        if(Helper::CoinToss()){
//            k = 2;
//        }
//
//        for(int i=1;i<=k;i++){
//            int a = position.x_ + dx[0] * i, b = position.y_ + dy[0] * i;
//            if(a < 0 || b < 0 || a >= 512 || b >= 512) continue;
//            int foo = Helper::GetIndex(a, b);
//            if((*buffer_)[foo] == NULL){
//                baz = foo;
//                continue;
//            }else break;
//        }
//
//        if(baz != -1){
//            (*buffer_)[index_]->last_frame_ = frame_count;
//            index_ = baz;
//            return;
//        }
//
//        for(int i=2;i<3;i++){
//            int a = position.x_ + dx[i], b = position.y_ + dy[i];
//            if(a < 0 || b < 0 || a >= 512 || b >= 512) continue;
//            int foo = Helper::GetIndex(a, b);
//            if((*buffer_)[foo] == NULL){
//                (*buffer_)[index_]->last_frame_ = frame_count;
//                index_ = foo;
//                return;
//            }
//        }
    }
};

#endif /* Sand_hpp */
