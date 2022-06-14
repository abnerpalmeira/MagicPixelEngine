#pragma once

#include "SDL2/SDL.h"

class Graphics
{
public:
	static void setRenderColor(SDL_Renderer *_ren, const SDL_Color *_col);
	static void drawCircle(SDL_Renderer *_ren, const SDL_Point *_center, const SDL_Rect *_bounds, Uint16 _rad);
	static Uint16 bresenhams(Sint32 _x1, Sint32 _y1, Sint32 _x2, Sint32 _y2, Sint32 *&_xOut, Sint32 *&_yOut, bool _fill);
};
