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
    size_ = w*h;
    chunk_ = chunk;
    max_x_ = min_x_+width_ -1;
    max_y_ = min_y_+height_ -1;
    last_frame_ = 0;
    live_pixel_ = 0;
    notify_ = 0;
    buffer_ = buffer;
    ResetRect();
}

void Chunk::UpdateRect(int x, int y) {
    dirty_rect_min_x_ = std::min(dirty_rect_min_x_,x);
    dirty_rect_min_y_ = std::min(dirty_rect_min_y_,y);
    dirty_rect_max_x_ = std::max(dirty_rect_max_x_,x);
    dirty_rect_max_y_ = std::max(dirty_rect_max_y_,y);
}

void Chunk::AddCell(int x, int y){
    live_pixel_++;
    UpdateRect(x, y);
}

void Chunk::RemoveCell(int x, int y){
    live_pixel_--;
    UpdateRect(x, y);
}

void  Chunk::MoveCell(int x,int y){
    int from = Helper::GetIndex(x, y);
    MagicPixel *current =(*buffer_)[from];
    if(current == nullptr || current->last_frame_ == frame_count) return;
    current->Update();
    int to = current->index_;
    if(from == to) return;
    int chunk = Helper::GetChunk(to);
    if(&chunk_[chunk] != this){
        Vector2 cord = Helper::GetCords(to);
        RemoveCell(cord.x_, cord.y_);
        chunk_[chunk].AddCell(cord.x_, cord.y_);
    }else{
        UpdateRect(x,y);
    }
    if(y && y == min_y_) notify_ |= 1;
    if(x && x == min_x_) notify_ |= 2;
    else if(x == max_x_ && x+1 < kSimulationWidth) notify_ |= 4;
    if(x && y && x == min_x_ && y == min_y_) notify_ |= 8;
    else if(y && x == max_x_ && x+1 < kSimulationWidth) notify_ |= 16;
}

void Chunk::NotifyPeers(){
    if(notify_ & 1){
        chunk_[Helper::GetChunk(Vector2(min_x_,min_y_-1))].NotifyBottom();
    }
    if(notify_ & 2){
        chunk_[Helper::GetChunk(Vector2(min_x_-1,min_y_))].NotifyLeft();
    }
    if(notify_ & 4){
        chunk_[Helper::GetChunk(Vector2(max_x_+1,min_y_))].NotifyRight();
    }
    if(notify_ & 8){
        chunk_[Helper::GetChunk(Vector2(min_x_-1,min_y_-1))].NotifyBottomLeft();
    }
    if(notify_ & 16){
        chunk_[Helper::GetChunk(Vector2(max_x_+1,min_y_-1))].NotifyBottomRight();
    }
}

void Chunk::NotifyBottom(){
    dirty_rect_max_y_ = max_y_;
    dirty_rect_min_x_ = min_x_;
    dirty_rect_max_x_ = max_x_;
}

void Chunk::NotifyLeft(){
    dirty_rect_max_x_ = max_x_;
    dirty_rect_min_y_ = min_y_;
    dirty_rect_max_y_ = max_y_;
}

void Chunk::NotifyRight(){
    dirty_rect_min_x_ = min_x_;
    dirty_rect_min_y_ = min_y_;
    dirty_rect_max_y_ = max_y_;
}

void Chunk::NotifyBottomLeft(){
    dirty_rect_max_x_ = max_x_;
    dirty_rect_max_y_ = max_y_;
}

void Chunk::NotifyBottomRight(){
    dirty_rect_min_x_ = min_x_;
    dirty_rect_max_y_ = max_y_;
}

void Chunk::ResetRect(){
    dirty_rect_min_x_ = max_x_;
    dirty_rect_min_y_ = max_y_;
    dirty_rect_max_x_ = min_x_;
    dirty_rect_max_y_ = min_y_;
}

void Chunk::Update(){
    if(!live_pixel_){
        last_frame_ = frame_count;
        return;
    }
    int min_x = std::max(dirty_rect_min_x_-1,min_x_);
    int min_y = std::max(dirty_rect_min_y_-1,min_y_);
    int max_x = std::min(dirty_rect_max_x_+1,max_x_);
    int max_y = std::min(dirty_rect_max_y_+1,max_y_);
    notify_ = 0;
    active_.clear();
    ResetRect();
    for(int i=min_x;i<=max_x;i++){
        for(int j=min_y;j<=max_y;j++){
            active_.push_back(Vector2(i,j));
        }
    }
    std::shuffle(active_.begin(), active_.end(), rng);
    for(int k = 0;k<active_.size();k++){
        MoveCell(active_[k].x_,active_[k].y_);
    }
    NotifyPeers();
    last_frame_ = frame_count;
}

