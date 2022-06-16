#include "Simulation.hpp"

Simulation::Simulation(int width, int height){
	width_ = width;
	height_ = height;
	size_ = width * height;
    buffer_ = std::vector<MagicPixel*>(size_,nullptr);
    chunk_ = new Chunk[64];
    jobs_ = new Job[64];
    int x = 0, y = 0;
    for(int i=0;i<64;i++){
        chunk_[i] = Chunk(x,y,kChunkSize,kChunkSize,chunk_,&buffer_);
        x += kChunkSize;
        if(x >= kSimulationWidth){
            x = 0;
            y += kChunkSize;
        }
        jobs_[i] = Job(chunk_[i]);
    }
    pool_.Start();
}

void Simulation::Reset(){
    for(int i=0;i<buffer_.size();i++){
        if(buffer_[i] != nullptr){
            delete buffer_[i];
            buffer_[i] = nullptr;
        }
        
    }
}

Simulation::~Simulation(){
    for(std::vector<MagicPixel *>::iterator it = buffer_.begin(); it != buffer_.end(); it++){
        if(*it != nullptr) delete *it;
    }
    delete[] chunk_;
	SDL_FreeFormat(pixel_format_);
    pool_.Stop();
}

void Simulation::ProcessChunk(int *chunks){
    int done = 0;
    for(int i=0;i<16;i++) pool_.QueueJob(jobs_[chunks[i]]);
    while(done != 16){
        done = 0;
        for(int i=0;i<16;i++) done += chunk_[chunks[i]].last_frame_ == frame_count;
    }
}

void Simulation::Update(){
    ProcessChunk(first_batch_);
    ProcessChunk(second_batch_);
    ProcessChunk(third_batch_);
    ProcessChunk(fourth_batch_);
}

void Simulation::SetCell(SDL_Point point, MaterialType material, bool physics){
    Uint32 index = point.x + point.y * width_;
    if(material == MaterialType::EMPTY && buffer_[index] != nullptr){
        delete buffer_[index];
        buffer_[index] = nullptr;
        chunk_[Helper::GetChunk(index)].RemoveCell(point.x,point.y);
    }
	else if(material != MaterialType::EMPTY && buffer_[index] == nullptr){
        buffer_[index] = Material::Init(index, material, &buffer_);
        chunk_[Helper::GetChunk(index)].AddCell(point.x,point.y);
        if(physics){
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        }
	}
}

void Simulation::SetCellInsideRadius(SDL_Point point, Uint16 rad, MaterialType material, bool physics){
    int sqr = rad * rad;
    for (int i = -rad; i <= rad; i++){
        for (int j = -rad; j <= rad; j++){
            if (i * i + j * j <= sqr){
                Sint32 x = point.x + i;
                Sint32 y = point.y + j;
                if(y >= 0 && y < height_ && x >= 0 && x < width_){
                    SetCell({x,y}, material,physics);
                }
            }
        }
    }
}
