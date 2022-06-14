#pragma once

#include <vector>
#include <stack>
#include <random>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <stdio.h>
#include <algorithm>
#include "ThreadPool.hpp"
#include "Global.hpp"
#include "Material.hpp"
#include "MagicPixel.hpp"
#include "Graphics.hpp"
#include "RandomAcessTable.hpp"
#include "Fenwick.hpp"
#include "Vector2.hpp"
#include "Chunk.hpp"
#include "Job.hpp"

const SDL_Color EMPTY_COLOR = {0, 0, 0, 0};

class Simulation
{
public:
    Simulation();
	Simulation(int _width, int _height);
	~Simulation();
	void Update();
    void Playground();
	void Reset();
    void SetCellRadius(SDL_Point pos, Uint16 rad, MaterialType mat, bool physics = false);
    Uint32 *draw_buffer_;
    std::vector<MagicPixel*> buffer_;
private:
    Chunk *chunk_;
    int *revive_,revive_count_;
	Uint16 width_, height_;
	Uint64 size_;
    ThreadPool pool_;
	SDL_PixelFormat *pixel_format_;
    Job *jobs_;
	void SetCell(Uint32 index, MaterialType mat, bool physics = false);
    void Red();
    void Green();
    void Blue();
    void Orange();
};
