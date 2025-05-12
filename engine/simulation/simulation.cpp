#pragma once

#include <array>
#include <memory>
#include <random>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <stdio.h>
#include <algorithm>
#include "common/geometry/vector.h"
#include "common/utility/helper.h"
#include "common/thread/job.h"
#include "common/thread/thread_pool.h"
#include "core/global.h"
#include "magicpixel/magic_pixel.h"
#include "simulation/chunk.h"
#include "simulation/buffer.h"

class Simulation{
public:
    Simulation();
	~Simulation();
	void Update();
    void Playground();
	void Reset();
    void SetCellInsideCircle(SDL_Point point, Uint16 rad, MaterialType material, bool physics = false);
    void SetCell(SDL_Point point, MaterialType material, bool physics = false);
    std::shared_ptr<Buffer> buffer_ptr_;
    std::shared_ptr<std::array<Chunk,kMaxChunk> > chunks_ptr_;
private:
    ThreadPool pool_;
    Job *jobs_;
    int first_batch_[kChunkBatchSize] = {0,4,10,14,16,20,26,30,32,36,42,46,48,52,58,62};
    int second_batch_[kChunkBatchSize] = {1,5,11,15,17,21,27,31,33,37,43,47,49,53,59,63};
    int third_batch_[kChunkBatchSize] = {2,6,8,12,18,22,24,28,34,38,40,44,50,54,56,60};
    int fourth_batch_[kChunkBatchSize] = {3,7,9,13,19,23,25,29,35,39,41,45,51,55,57,61};
    void ProcessChunk(int *chunks);
};
