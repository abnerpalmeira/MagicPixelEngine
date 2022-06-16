//
//  Navigation.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//


#include "Movable.hpp"

void Movable::MoveStep(int step,int dir){
    int new_index = -1;
    for(int i=0;i<step;i++){
        int a = position_.x_ + dx_[dir], b = position_.y_ + dy_[dir];
        if(a < 0 || b < 0 || a >= kSimulationWidth || b >= kScreenHeight) continue;
        int bar = Helper::GetIndex(a, b);
        if(CanMove(bar)){
            new_index = bar;
            last_frame_ = frame_count;
            continue;
        }
        else break;
    }
    if(new_index != -1) UpdateIndex(new_index);
    return;
}

Vector2 Movable::LineCover(Vector2 target, bool super){
    bool swap = false;
    int x = position_.x_, y = position_.y_;
    int dx = target.x_-position_.x_, dy = target.y_-position_.y_;
    auto cmp = [](int a,int b) { return (a < b)?-1:1; };
    if(cmp(abs(dx),abs(dy)) < 0){
        swap = true;
        std::swap(x,y);
        std::swap(dx,dy);
    }
    int x_step = cmp(0,dx), y_step = cmp(0,dy);
    dx = abs(dx);
    dy = abs(dy);
    int ddx = 2*dx, ddy = 2*dy;
    int errorprev = dy, error = dy;
    Vector2 foo;
    for(int i = 0;i<dy;i++){
        y += y_step;
        error += ddx;
        if(error > ddy){
            x += x_step;
            error -= ddy;
            if(super){
                if(error + errorprev <= ddy){
                    foo = Vector2(x-x_step,y);
                }
                if(error + errorprev >= ddy){
                    foo = Vector2(x,y-y_step);
                }
            }
        }
        foo = Vector2(x,y);
    }
    return foo;
}
