//
//  Chunk.cpp
//  2D Sand
//
//  Created by Abner Palmeira on 05/06/22.
//

#include "Chunk.hpp"

Chunk::Chunk(int x, int y, int w, int h, Chunk *chunk, std::vector<MagicPixel*> *buffer){
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    size_ = w*h;
    chunk_ = chunk;
    xw_ = x_+w_ -1;
    yh_ = y_+h_ -1;
    last_frame_ = 0;
    live_pixel_ = 0;
    notify_ = 0;
    buffer_ = buffer;
    ResetRect();
}

void Chunk::UpdateRect(int x, int y) {
    min_x_ = std::min(min_x_,x);
    min_y_ = std::min(min_y_,y);
    max_x_ = std::max(max_x_,x);
    max_y_ = std::max(max_y_,y);
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
        UpdateRect(cord.x_, cord.y_);
        chunk_[chunk].AddCell(cord.x_, cord.y_);
    }else{
        min_x_ = std::min(min_x_,x);
        min_y_ = std::min(min_y_,y);
        max_x_ = std::max(max_x_,x);
        max_y_ = std::max(max_y_,y);
    }
    if(y && y == y_) notify_ |= 1;
    if(x && x == x_) notify_ |= 2;
    else if(x == xw_ && x+1 < kSimulationWidth) notify_ |= 4;
    if(x && y && x == x_ && y == y_) notify_ |= 8;
    else if(y && x == xw_ && x+1 < kSimulationWidth) notify_ |= 16;
}

void Chunk::NotifyPeers(){
    if(notify_ & 1){
        chunk_[Helper::GetChunk(Vector2(x_,y_-1))].NotifyBottom();
    }
    if(notify_ & 2){
        chunk_[Helper::GetChunk(Vector2(x_-1,y_))].NotifyLeft();
    }
    if(notify_ & 4){
        chunk_[Helper::GetChunk(Vector2(xw_+1,y_))].NotifyRight();
    }
    if(notify_ & 8){
        chunk_[Helper::GetChunk(Vector2(x_-1,y_-1))].NotifyBottomLeft();
    }
    if(notify_ & 16){
        chunk_[Helper::GetChunk(Vector2(xw_+1,y_-1))].NotifyBottomRight();
    }
}

void Chunk::NotifyBottom(){
    max_y_ = yh_;
    min_x_ = x_;
    max_x_ = xw_;
}

void Chunk::NotifyLeft(){
    max_x_ = xw_;
    min_y_ = y_;
    max_y_ = yh_;
}

void Chunk::NotifyRight(){
    min_x_ = x_;
    min_y_ = y_;
    max_y_ = yh_;
}

void Chunk::NotifyBottomLeft(){
    max_x_ = xw_;
    max_y_ = yh_;
}

void Chunk::NotifyBottomRight(){
    min_x_ = x_;
    max_y_ = yh_;
}

void Chunk::ResetRect(){
    min_x_ = xw_;
    min_y_ = yh_;
    max_x_ = x_;
    max_y_ = y_;
}

void Chunk::Update(){
    if(!live_pixel_){
        last_frame_ = frame_count;
        return;
    }
    int min_x = std::max(min_x_-1,x_);
    int min_y = std::max(min_y_-1,y_);
    int max_x = std::min(max_x_+1,xw_);
    int max_y = std::min(max_y_+1,yh_);
    notify_ = 0;
    active_.clear();
    ResetRect();
    for(int i=min_x;i<=max_x;i++){
        for(int j=min_y;j<=max_y;j++){
            active_.push_back(Vector2(i,j));
        }
    }
    std::shuffle(active_.begin(), active_.end(), rng);
//    for (int i = 0; i < active_.size(); i++){
//        std::swap(active_[i], active_[std::uniform_int_distribution<int>(0, i)(rng)]);
//    }
    for(int k = 0;k<active_.size();k++){
        MoveCell(active_[k].x_,active_[k].y_);
    }
    NotifyPeers();
    last_frame_ = frame_count;
}

