//
//  Global.cpp
//  2D Sand
//
//  Created by Abner Palmeira on 03/06/22.
//

#include "Global.hpp"
Uint32 frame_count = 0;
Uint32 current_tick = 0;
Uint32 last_tick = 0;
float delta_time = 0;
SDL_PixelFormat* pixel_format = SDL_AllocFormat(kPixelFormat);
std::mt19937 rng;
Uint32 empty_pixel_value = SDL_MapRGBA(pixel_format, 0, 0, 0, 0);
