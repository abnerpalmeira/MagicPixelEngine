//
//  global.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 03/06/22.
//

#include "core/global.h"

Uint32 frame_count = 0;
Uint32 current_tick = 0;
Uint32 last_tick = 0;
float delta_time = 0;
SDL_PixelFormat* pixel_format = SDL_AllocFormat(kPixelFormat);
Uint32 kEmptyPixelValue = SDL_MapRGBA(pixel_format, 0, 0, 0, 0);
SDL_Point cursor = {-1,-1};
TTF_Font *font = nullptr;

thread_local std::mt19937 rng;
