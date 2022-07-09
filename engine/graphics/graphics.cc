#include <algorithm>
#include "graphics/graphics.h"

void Graphics::DrawCircle(SDL_Renderer *renderer, const SDL_Point *center, const SDL_Rect *bounds, Uint16 radius){
	if(!SDL_PointInRect(center, bounds)) { return; }

	Sint32 x = radius;
	Sint32 y = 0;
	Sint32 tx = 1;
	Sint32 ty = 1;
	Sint32 error = tx - radius * 2;

	while(x >= y){
		Sint32 lookup[16] = {x, -y, x, y, -x, -y, -x, y, y, -x, y, x, -y, -x, -y, x};
		for(int i = 0; i < 8; ++i)
		{
			Sint32 drawX = std::clamp(center->x + lookup[i * 2], bounds->x, bounds->x + bounds->w);
			Sint32 drawY = std::clamp(center->y + lookup[i * 2 + 1], bounds->y, bounds->y + bounds->h - 1);
			SDL_RenderDrawPoint(renderer, drawX, drawY);
		}
		if(error <= 0){
			++y;
			ty += 2;
			error += ty;
		}
		if(error > 0){
			--x;
			tx += 2;
			error += tx - radius * 2;
		}
	}
}
