//
//  Chunk.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 05/06/22.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <chrono>
#include <stdio.h>
#include <algorithm>
#include "Global.hpp"
#include "RandomAcessTable.hpp"
#include "MagicPixel.hpp"
#include "SDL2/SDL.h"

class Chunk{
public:
    Chunk *chunk_;
    std::vector<MagicPixel*> *buffer_;
    Uint32 last_frame_;
    std::vector<Vector2> active_;
    int notify_;
    int dirty_rect_min_x_,dirty_rect_min_y_;
    int dirty_rect_max_x_,dirty_rect_max_y_;
    int min_x_,min_y_;
    int max_x_,max_y_;
    int width_,height_;
    int size_;
    int live_pixel_;
    Chunk(){};
    Chunk(int x, int y, int w, int h, Chunk *chunk, std::vector<MagicPixel*> *buffer);
    void Debug(SDL_Renderer *renderer,float scale);
    void Update();
    void UpdateRect(int x, int y);
    void AddCell(int x, int y);
    void RemoveCell(int x, int y);
    void Notify(int x, int y);
    
    void MoveCell(int from,int to);
    void NotifyBottom(int min_x,int max_x);
    void NotifyLeft(int min_y,int max_y);
    void NotifyRight(int min_y,int max_y);
    void NotifyBottomLeft();
    void NotifyBottomRight();
    void ResetRect();
    void NotifyPeers();
};

#endif /* Chunk_hpp */
