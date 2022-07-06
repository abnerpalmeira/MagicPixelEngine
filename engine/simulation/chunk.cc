//
//  chunk.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 05/06/22.
//

#include "chunk.h"

void Chunk::Init(int x, int y, std::shared_ptr<std::array<Chunk,kMaxChunk> > chunks, std::shared_ptr<Buffer> buffer){
    buffer_ptr_ = buffer;
    chunks_ = chunks;
    min_x_ = x;
    min_y_ = y;
    max_x_ = min_x_+kMaxChunk - 1;
    max_y_ = min_y_+kMaxChunk - 1;
    last_frame_ = 0;
    live_pixel_ = 0;
    ResetRect();
}

void Chunk::UpdateRect(int x, int y) {
    dirty_rect_min_x_ = std::min(x,dirty_rect_min_x_);
    dirty_rect_min_y_ = std::min(y,dirty_rect_min_y_);
    dirty_rect_max_x_ = std::max(x,dirty_rect_max_x_);
    dirty_rect_max_y_ = std::max(y,dirty_rect_max_y_);
}

void Chunk::GetCurrentDirtyRect(int &max_x, int &max_y, int &min_x, int &min_y) {
    min_x = std::clamp(dirty_rect_min_x_-1,0,511);
    min_y = std::clamp(dirty_rect_min_y_-1,0,511);
    max_x = std::clamp(dirty_rect_max_x_+1,0,511);
    max_y = std::clamp(dirty_rect_max_y_+1,0,511);
}

void Chunk::AddCell(MaterialType material,int x, int y){
    if(!buffer_ptr_->IsCellEmpty(x, y)) return;
    buffer_ptr_->CreateMagicPixel(material, x, y);
}

void Chunk::RemoveCell(int x, int y){
    buffer_ptr_->RemoveMagicPixel(x, y);
}

void Chunk::ResetRect(){
    dirty_rect_min_x_ = max_x_;
    dirty_rect_min_y_ = max_y_;
    dirty_rect_max_x_ = min_x_;
    dirty_rect_max_y_ = min_y_;
}

void Chunk::Update(){
    ResetRect();
    for(int i=min_x_;i<=max_x_;i++){
        for(int j=min_y_;j<=max_y_;j++){
            if(buffer_ptr_->IsExpired(i,j)) buffer_ptr_->RemoveMagicPixel(i, j);
            if(buffer_ptr_->buffer_[i][j].update_) UpdateRect(i, j);
        }
    }
    int min_x,min_y,max_x,max_y;
    GetCurrentDirtyRect(max_x, max_y, min_x, min_y);
    active_.clear();
    for(int i=min_x;i<=max_x;i++){
        for(int j=min_y;j<=max_y;j++){
            active_.push_back(Vector2(i,j));
        }
    }
    std::shuffle(active_.begin(), active_.end(), rng);
    for(int i = 0;i<active_.size();i++){
        buffer_ptr_->buffer_[active_[i].x_][active_[i].y_].Update(*buffer_ptr_);
    }
    last_frame_ = frame_count;
}

void Chunk::Debug(SDL_Renderer *renderer,float scale){
    SDL_FRect rectToDraw = {scale*min_x_,scale*min_y_,scale*kMaxChunk,scale*kMaxChunk};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRectF(renderer, &rectToDraw);
    int min_x,min_y,max_x,max_y;
    GetCurrentDirtyRect(max_x, max_y, min_x, min_y);
    if(min_x <= max_x && min_y <= max_y){
        rectToDraw = {scale*min_x,scale*min_y,scale*(max_x-min_x+1),scale*(max_y-min_y+1)};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRectF(renderer, &rectToDraw);
    }
}
