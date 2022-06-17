//
//  Chunk.cpp
//  2D Sand
//
//  Created by Abner Palmeira on 05/06/22.
//

#include "Chunk.hpp"

Chunk::Chunk(int x, int y, int w, int h, Chunk *chunk, std::vector<MagicPixel*> *buffer){
    min_x_ = x;
    min_y_ = y;
    width_ = w;
    height_ = h;
    max_x_ = min_x_+width_ -1;
    max_y_ = min_y_+height_ -1;
    size_ = width_*height_;
    chunk_ = chunk;
    last_frame_ = 0;
    live_pixel_ = 0;
    notify_ = 0;
    buffer_ = buffer;
    ResetRect();
}

void Chunk::UpdateRect(int x, int y) {
    dirty_rect_min_x_ = std::min(x,dirty_rect_min_x_);
    dirty_rect_min_y_ = std::min(y,dirty_rect_min_y_);
    dirty_rect_max_x_ = std::max(x,dirty_rect_max_x_);
    dirty_rect_max_y_ = std::max(y,dirty_rect_max_y_);
}

void Chunk::AddCell(int x, int y){
    live_pixel_++;
    UpdateRect(x, y);
}

void Chunk::RemoveCell(int x, int y){
    live_pixel_--;
    UpdateRect(x, y);
}

void Chunk::Notify(int x, int y) {
    if(y == min_y_ && y) notify_ |= 1;
    if(x == min_x_ && x) notify_ |= 2;
    else if(x == max_x_ && x+1 < kSimulationWidth) notify_ |= 4;
    if(x == min_x_ && y == min_y_ && x && y) notify_ |= 8;
    else if(x == max_x_ && y == min_y_ && x+1 < kSimulationWidth && y) notify_ |= 16;
}

void  Chunk::ProcessCell(int x,int y){
    int from = Helper::GetIndex(x, y);
    MagicPixel *current =(*buffer_)[from];
    if(current == nullptr || current->last_frame_ == frame_count) return;
    current->Update();
    if(from == current->index_) return;
    int chunk = Helper::GetChunk(current->index_);
    if(&chunk_[chunk] != this){
        Vector2 cord = current->position_;
        live_pixel_--;
        chunk_[chunk].AddCell(cord.x_, cord.y_);
    }
    UpdateRect(x,y);
}

void Chunk::NotifyPeers(){
    if(notify_ & 1){
        chunk_[Helper::GetChunk(Vector2(min_x_,min_y_-1))].NotifyBottom(dirty_rect_min_x_,dirty_rect_max_x_);
    }
    if(notify_ & 2){
        chunk_[Helper::GetChunk(Vector2(min_x_-1,min_y_))].NotifyRight(dirty_rect_min_y_,dirty_rect_max_y_);
    }
    if(notify_ & 4){
        chunk_[Helper::GetChunk(Vector2(max_x_+1,min_y_))].NotifyLeft(dirty_rect_min_y_,dirty_rect_max_y_);
    }
    if(notify_ & 8){
        chunk_[Helper::GetChunk(Vector2(min_x_-1,min_y_-1))].NotifyBottomRight();
    }
    if(notify_ & 16){
        chunk_[Helper::GetChunk(Vector2(max_x_+1,min_y_-1))].NotifyBottomLeft();
    }
}

void Chunk::NotifyBottom(int min_x,int max_x){
    dirty_rect_max_y_ = max_y_;
    dirty_rect_min_x_ = std::min(min_x,dirty_rect_min_x_);
    dirty_rect_max_x_ = std::max(max_x,dirty_rect_max_x_);
}

void Chunk::NotifyLeft(int min_y,int max_y){
    dirty_rect_min_x_ = min_x_;
    dirty_rect_min_y_ = std::min(min_y,dirty_rect_min_y_);
    dirty_rect_max_y_ = std::max(max_y,dirty_rect_max_y_);
}

void Chunk::NotifyRight(int min_y,int max_y){
    dirty_rect_max_x_ = max_x_;
    dirty_rect_min_y_ = std::min(min_y,dirty_rect_min_y_);
    dirty_rect_max_y_ = std::max(max_y,dirty_rect_max_y_);
}

void Chunk::NotifyBottomLeft(){
    dirty_rect_min_x_ = min_x_;
    dirty_rect_max_y_ = max_y_;
}

void Chunk::NotifyBottomRight(){
    dirty_rect_max_x_ = max_x_;
    dirty_rect_max_y_ = max_y_;
}

void Chunk::ResetRect(){
    dirty_rect_min_x_ = max_x_;
    dirty_rect_min_y_ = max_y_;
    dirty_rect_max_x_ = min_x_;
    dirty_rect_max_y_ = min_y_;
}

void Chunk::GetCurrentDirtyRect(int &max_x, int &max_y, int &min_x, int &min_y) {
    min_x = std::clamp(dirty_rect_min_x_-1,min_x_,max_x_);
    min_y = std::clamp(dirty_rect_min_y_-1,min_y_,max_y_);
    max_x = std::clamp(dirty_rect_max_x_+1,min_x_,max_x_);
    max_y = std::clamp(dirty_rect_max_y_+1,min_y_,max_y_);
}

void Chunk::Update(){
    if(!live_pixel_){
        last_frame_ = frame_count;
        return;
    }
    int min_x,min_y,max_x,max_y;
    GetCurrentDirtyRect(max_x, max_y, min_x, min_y);
    ResetRect();
    notify_ = 0;
    active_.clear();
    for(int i=min_x;i<=max_x;i++){
        for(int j=min_y;j<=max_y;j++){
            active_.push_back(Vector2(i,j));
        }
    }
    std::shuffle(active_.begin(), active_.end(), rng);
    for(int k = 0;k<active_.size();k++){
        ProcessCell(active_[k].x_,active_[k].y_);
    }
    if(dirty_rect_min_x_ <= dirty_rect_max_x_ && dirty_rect_min_y_ <= dirty_rect_max_y_){
        Notify(dirty_rect_min_x_, dirty_rect_min_y_);
        Notify(dirty_rect_max_x_, dirty_rect_min_y_);
        NotifyPeers();
    }
    last_frame_ = frame_count;
}

void Chunk::Debug(SDL_Renderer *renderer,float scale){
    SDL_FRect rectToDraw = {scale*min_x_,scale*min_y_,scale*width_,scale*height_};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRectF(renderer, &rectToDraw);
    int min_x,min_y,max_x,max_y;
    GetCurrentDirtyRect(max_x, max_y, min_x, min_y);
    if(live_pixel_ && min_x <= max_x && min_y <= max_y_){
        rectToDraw = {scale*min_x,scale*min_y,scale*(max_x-min_x+1),scale*(max_y-min_y+1)};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRectF(renderer, &rectToDraw);
    }
}
