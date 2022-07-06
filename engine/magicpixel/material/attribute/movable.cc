//
//  movable.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 14/06/22.
//


#include "movable.h"

bool Movable::MoveStep(Buffer &buffer,int step,int direction,int x,int y){
    int a = x, b = y;
    int next_x = x, next_y = y;
    for(int i=0;i<step;i++){
        a += dx_[direction];
        b += dy_[direction];
        if(a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) break;
        int can_move = CanMove(buffer,a,b);
        if(can_move == 1){
            next_x = a;
            next_y = b;
            continue;
        }else if(!can_move){
            break;
        }
    }
    if(next_x != x || next_y != y){
        buffer.MoveCell(x,y,next_x,next_y);
        return true;
    }
    return false;
}

bool Movable::LineCover(Buffer &buffer, Vector2 target,int x, int y, bool super){
//    bool swap = false;
//    int x = position_.x_, y = position_.y_;
//    int dx = target.x_-position_.x_, dy = target.y_-position_.y_;
//    auto cmp = [](int a,int b) { return (a < b)?-1:1; };
//    if(cmp(abs(dx),abs(dy)) < 0){
//        swap = true;
//        std::swap(x,y);
//        std::swap(dx,dy);
//    }
//    int x_step = cmp(0,dx), y_step = cmp(0,dy);
//    dx = abs(dx);
//    dy = abs(dy);
//    int ddx = 2*dx, ddy = 2*dy;
//    int errorprev = dy, error = dy;
//    Vector2 ans = position_;
//    for(int i = 0;i<dy;i++){
//        y += y_step;
//        error += ddx;
//        if(error > ddy){
//            x += x_step;
//            error -= ddy;
//            if(super){
//                if(error + errorprev <= ddy){
//                    Vector2(x-x_step,y);
//                }
//                if(error + errorprev >= ddy){
//                    Vector2(x,y-y_step);
//                }
//            }
//        }
//        int bar = Helper::GetIndex(x, y);
//        if(CanMove(bar)){
//            ans = Vector2(x,y);
//            last_frame_ = frame_count;
//        }
//    }
//    if(swap) std::swap(ans.x_,ans.y_);
//    return ans;
    return true;
}
