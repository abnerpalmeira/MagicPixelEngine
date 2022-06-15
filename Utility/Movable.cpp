//
//  Navigation.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//


#include "Movable.hpp"

Vector2 Movable::MoveStep(int step,int dir){
    Vector2 foo = position_;
    for(int i=0;i<step;i++){
        int a = foo.x_ + dx[dir], b = foo.y_ + dy[dir];
        if(a < 0 || b < 0 || a >= kSimulationWidth || b >= kScreenHeight) continue;
        int bar = Helper::GetIndex(a, b);
        if(CanMove(bar)){
            foo.x_ = a;
            foo.y_ = b;
            continue;
        }
        else break;
    }
    if(foo != position_) UpdatePosition(foo);
    return foo;
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
