//
//  chunk.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 05/06/22.
//

#pragma once

#include <algorithm>
#include <memory>
#include <SDL.h>
#include "simulation/buffer.h"
#include "core/global.h"
#include "magicpixel/magic_pixel.h"
#include "magicpixel/material/material_type.h"

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
    void ResetRect();
    std::shared_ptr<Buffer> buffer_ptr_;
    std::shared_ptr<std::array<Chunk,kMaxChunk> > chunks_;
    std::vector<Vector2> active_;
    Uint32 last_frame_;
    int dirty_rect_min_x_,dirty_rect_min_y_;
    int dirty_rect_max_x_,dirty_rect_max_y_;
    int min_x_,min_y_;
    int max_x_,max_y_;
    int live_pixel_;
};
