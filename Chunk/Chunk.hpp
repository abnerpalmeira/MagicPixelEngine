//
//  Chunk.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 05/06/22.
//

#pragma once

#include <algorithm>
#include <memory>
#include "SDL2/SDL.h"
#include "Buffer.hpp"
#include "Global.hpp"
#include "MagicPixel.hpp"
#include "MaterialType.hpp"

class Chunk{
public:
    Chunk() = default;
    void Init(int x, int y, std::shared_ptr<std::array<Chunk,kMaxChunk> > chunks, std::shared_ptr<Buffer> buffer);
    void Debug(SDL_Renderer *renderer,float scale);
    void GetCurrentDirtyRect(int &max_x, int &max_y, int &min_x, int &min_y);
    void Update();
    void UpdateRect(int x, int y);
    void AddCell(MaterialType material,int x, int y);
    void RemoveCell(int x, int y);
    void Notify(int x, int y);
    void ProcessCell(int from,int to);
    void NotifyTop(int min_x,int max_x);
    void NotifyBottom(int min_x,int max_x);
    void NotifyLeft(int min_y,int max_y);
    void NotifyRight(int min_y,int max_y);
    void NotifyBottomLeft();
    void NotifyBottomRight();
    void ResetRect();
    void NotifyPeers();
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
    std::shared_ptr<Buffer> buffer_ptr_;
    std::shared_ptr<std::array<Chunk,kMaxChunk> > chunks_;
    std::vector<Vector2> active_;
    Uint32 last_frame_;
    int check_all_;
    int notify_;
    int dirty_rect_min_x_,dirty_rect_min_y_;
    int dirty_rect_max_x_,dirty_rect_max_y_;
    int min_x_,min_y_;
    int max_x_,max_y_;
    int live_pixel_;
};
