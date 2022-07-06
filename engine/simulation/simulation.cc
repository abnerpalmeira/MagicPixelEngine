#include "simulation.h"

Simulation::Simulation(){
    buffer_ptr_ = std::make_shared<Buffer>();
    chunks_ptr_ = std::make_shared<std::array<Chunk,kMaxChunk> >();
    jobs_ = new Job[64];
    int x = 0, y = 0;
    for(int i=0;i<chunks_ptr_->size();i++){
        (*chunks_ptr_)[i].Init(x,y,chunks_ptr_,buffer_ptr_);
        x += kMaxChunk;
        if(x >= kSimulationWidth){
            x = 0;
            y += kMaxChunk;
        }
        jobs_[i] = Job((*chunks_ptr_)[i]);
    }
    pool_.Start();
}

void Simulation::Reset(){
    buffer_ptr_->Reset();
}

Simulation::~Simulation(){
    pool_.Stop();
}

void Simulation::ProcessChunk(int *chunks){
    int done = 0;
    for(int i=0;i<16;i++) pool_.QueueJob(jobs_[chunks[i]]);
    while(done != 16){
        done = 0;
        for(int i=0;i<16;i++) done += (*chunks_ptr_)[chunks[i]].last_frame_ == frame_count;
    }
}

void Simulation::Update(){
    ProcessChunk(first_batch_);
    ProcessChunk(second_batch_);
    ProcessChunk(third_batch_);
    ProcessChunk(fourth_batch_);
}

void Simulation::SetCell(SDL_Point point, MaterialType material, bool physics){
    Uint32 index = point.x + point.y * kSimulationWidth;
    if(material == MaterialType::EMPTY){
        (*chunks_ptr_)[Helper::GetChunk(index)].RemoveCell(point.x,point.y);
    }
	else if(material != MaterialType::EMPTY ){
        (*chunks_ptr_)[Helper::GetChunk(index)].AddCell(material,point.x,point.y);
        if(physics){
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        }
	}
}

void Simulation::SetCellInsideCircle(SDL_Point point, Uint16 rad, MaterialType material, bool physics){
    int sqr = rad * rad;
    for (int i = -rad; i <= rad; i++){
        for (int j = -rad; j <= rad; j++){
            if (i * i + j * j <= sqr){
                Sint32 x = point.x + i;
                Sint32 y = point.y + j;
                if(y >= 0 && y < kSimulationHeight && x >= 0 && x < kSimulationWidth){
                    SetCell({x,y}, material,physics);
                }
            }
        }
    }
}
