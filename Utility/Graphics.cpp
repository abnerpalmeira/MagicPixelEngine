#include "Graphics.hpp"

#include <algorithm>

void Graphics::setRenderColor(SDL_Renderer *_ren, const SDL_Color *_col)
{
	SDL_SetRenderDrawColor(_ren, _col->r, _col->g, _col->b, _col->a);
}

//Uses a modified version of the Midpoint Circle Algorithm
void Graphics::drawCircle(SDL_Renderer *_ren, const SDL_Point *_center, const SDL_Rect *_bounds, Uint16 _rad)
{
	if(!SDL_PointInRect(_center, _bounds)) { return; }

	Sint32 x = _rad;
	Sint32 y = 0;
	Sint32 tx = 1;
	Sint32 ty = 1;
	Sint32 error = tx - _rad * 2;

	while(x >= y)
	{
		Sint32 lookup[16] = {x, -y, x, y, -x, -y, -x, y, y, -x, y, x, -y, -x, -y, x};
		for(int i = 0; i < 8; ++i)
		{
			Sint32 drawX = std::clamp(_center->x + lookup[i * 2], _bounds->x, _bounds->x + _bounds->w);
			Sint32 drawY = std::clamp(_center->y + lookup[i * 2 + 1], _bounds->y, _bounds->y + _bounds->h - 1);
			SDL_RenderDrawPoint(_ren, drawX, drawY);
		}

		if(error <= 0)
		{
			++y;
			ty += 2;
			error += ty;
		}
		if(error > 0)
		{
			--x;
			tx += 2;
			error += tx - _rad * 2;
		}
	}
}
