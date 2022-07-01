#pragma once

#include "SDL2/SDL.h"

class Graphics
{
public:
	static void DrawCircle(SDL_Renderer *renderer, const SDL_Point *center, const SDL_Rect *bounds, Uint16 radius);
};
