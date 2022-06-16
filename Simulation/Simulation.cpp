#include "Simulation.hpp"

Simulation::Simulation(int width, int height){
	width_ = width;
	height_ = height;
	size_ = width * height;
    buffer_ = std::vector<MagicPixel*>(size_,nullptr);
    revive_ = new int[size_];
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
	Reset();
}

void Simulation::Reset(){
    
}

Simulation::~Simulation(){
    for(std::vector<MagicPixel *>::iterator it = buffer_.begin(); it != buffer_.end(); it++){
        if(*it != NULL) delete *it;
    }
    delete[] chunk_;
	SDL_FreeFormat(pixel_format_);
    pool_.Stop();
}

void Simulation::Red(){
    int done = 0;
    int red[] = {0,4,10,14,16,20,26,30,32,36,42,46,48,52,58,62};
    for(int i=0;i<16;i++) pool_.QueueJob(jobs_[red[i]]);
    while(done != 16){
        done = 0;
        for(int i=0;i<16;i++) done += chunk_[red[i]].last_frame_ == frame_count;
    }
}

void Simulation::Green(){
    int done = 0;
    int green[] = {1,5,11,15,17,21,27,31,33,37,43,47,49,53,59,63};
    for(int i=0;i<16;i++) pool_.QueueJob(jobs_[green[i]]);
    while(done != 16){
        done = 0;
        for(int i=0;i<16;i++) done += chunk_[green[i]].last_frame_ == frame_count;
    }
}

void Simulation::Blue(){
    int done = 0;
    int blue[] = {2,6,8,12,18,22,24,28,34,38,40,44,50,54,56,60};
    for(int i=0;i<16;i++) pool_.QueueJob(jobs_[blue[i]]);
    while(done != 16){
        done = 0;
        for(int i=0;i<16;i++) done += chunk_[blue[i]].last_frame_ == frame_count;
    }
}

void Simulation::Orange(){
    int done = 0;
    int orange[] = {3,7,9,13,19,23,25,29,35,39,41,45,51,55,57,61};
    for(int i=0;i<16;i++) pool_.QueueJob(jobs_[orange[i]]);
    while(done != 16){
        done = 0;
        for(int i=0;i<16;i++) done += chunk_[orange[i]].last_frame_ == frame_count;
    }
}

void Simulation::Update(){
//    typedef void (Simulation::*method_function)();
//    method_function arr[] = {&Simulation::Red,&Simulation::Green,&Simulation::Blue,&Simulation::Orange};
//    std::random_device rd;
//    std::mt19937 g(rd());
//    std::shuffle(arr, arr+4, g);
//    for(int i=0;i<4;i++){
//        method_function func = arr[i];
//        (this->*func)();
//    }
    Red();
    Green();
    Blue();
    Orange();

}

void Simulation::SetCell(Uint32 index, MaterialType material, bool physics){
    if(material == MaterialType::EMPTY && buffer_[index] != nullptr){
        delete buffer_[index];
        buffer_[index] = nullptr;
    }
	else if(material != MaterialType::EMPTY && buffer_[index] == nullptr){
        buffer_[index] = Material::Init(index, material, &buffer_);
        if(physics){
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
//            buffer_[_index].velocity_ = Vector2(std::uniform_int_distribution<int>(0, 5)(rng),std::uniform_int_distribution<int>(0, 5)(rng));
//            buffer_[_index].has_velocity_ = true;
        }
	}
}

//Sets a circle of cells by radius for user input
void Simulation::SetCellRadius(SDL_Point point, Uint16 rad, MaterialType material, bool physics){
    int sqr = rad * rad;
    for (int i = -rad; i <= rad; i++){
        for (int j = -rad; j <= rad; j++){
            if (i * i + j * j <= sqr){
                Sint32 x = point.x + i;
                Sint32 y = point.y + j;
                Uint32 index = x + y * width_;
                if(y >= 0 && y < height_ && x >= 0 && x < width_){
                    SetCell(index, material,physics);
                    if(material != MaterialType::EMPTY) chunk_[Helper::GetChunk(index)].AddCell(x,y);
                    else chunk_[Helper::GetChunk(index)].RemoveCell(x,y);
                }
                
            }
        }
    }
}
