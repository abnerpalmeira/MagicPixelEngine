//
//  helper.h
//  2D Sand
//
//  Created by Abner Palmeira on 01/06/22.
//
#pragma once

#include <stdio.h>
#include <vector>
#include <utility>
#include <iostream>
#include "SDL2/SDL.h"
#include "global.h"
#include "vector.h"

class Helper{
public:
    
    static SDL_Rect *Init(int XPos, int YPos, int Width, int Height){
        SDL_Rect *Rect = new SDL_Rect;
        Rect->h = Height;
        Rect->w = Width;
        Rect->x = XPos;
        Rect->y = YPos;

        return Rect;
    }
    
    static int GetIndex(int x, int y){
        return x + (y << kSimulationWidthPower2Expoent);
    }
    
    static Vector2 GetCords(int idx){
        return Vector2((double)(idx & (kSimulationWidth-1)),(double)(idx >> kSimulationWidthPower2Expoent));
    }
    
    static int GetChunk(int idx){
        return GetChunk(GetCords(idx));
    }
    
    static int GetChunk(Vector2 cord){
        int x = cord.x_, y = cord.y_;
        return (y >> 6) * (kSimulationWidth >> 6) + (x >> 6);
    }
    
    static int GetChunk(int x,int y){
        return (y >> 6) * (kSimulationWidth >> 6) + (x >> 6);
    }
    
    static int ScreenWidthPoint(int x){
        return x * kScreenWidth/16;
    }
    
    static int ScreenHeightPoint(int y){
        return y * kScreenHeight/9;
    }
    
    static double RandomDoubleOnInterval(double min, double max){
        return std::uniform_real_distribution<double>(min, max )(rng);
    }
    
    static int RandomIntOnInterval(int min, int max){
        return std::uniform_int_distribution<int>(min, max)(rng);
    }
    
    static bool CoinToss(){
        return std::uniform_int_distribution<int>(0, 1)(rng);
    }
    //http://oeis.org/A295344
    static std::vector<Vector2> LatticePointsOnCircle(int radius,Vector2 center = Vector2(0,0)){
        int sqrRadius = radius * radius;
        std::vector<Vector2> points = std::vector<Vector2>();
        for (int i = -radius; i <= radius; i++){
            for (int j = -radius; j <= radius; j++){
                if (i * i + j * j <= sqrRadius){
                    points.push_back(center + Vector2(i,j));
                }
            }
        }
        return points;
    }
    //http://eugen.dedu.free.fr/projects/bresenham/
    static std::vector<Vector2> LineCover(Vector2 a, Vector2 b, bool super = false){
        bool swap = false;
        int x = a.x_, y = a.y_;
        int dx = b.x_-a.x_, dy = b.y_-a.y_;
        std::vector<Vector2> points = std::vector<Vector2>();
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
                        points.push_back(a - foo);
                    }
                    if(error + errorprev >= ddy){
                        foo = Vector2(x,y-y_step);
                        points.push_back(a - foo);
                    }
                }
            }
            foo = Vector2(x,y);
            points.push_back(a - foo);
        }
        if(swap){
            for(int i=0;i<points.size();i++){
                std::swap(points[i].x_,points[i].y_);
            }
        }
        return points;
    }
    
    static Vector2 LastPoint(Vector2 a, Vector2 b, bool super = false){
        bool swap = false;
        int x = a.x_, y = a.y_;
        int dx = b.x_-a.x_, dy = b.y_-a.y_;
        Vector2 points = a;
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
            points = a - foo;
        }
        if(swap){
            std::swap(points.x_,points.y_);
            
        }
        return points;
    }
};
