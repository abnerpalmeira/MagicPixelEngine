//
//  Global.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 03/06/22.
//

#ifndef Global_hpp
#define Global_hpp
#include "SDL2/SDL.h"

extern Uint32 frame_count;
extern Uint32 current_tick;
extern Uint32 last_tick;
extern float delta_time;
extern SDL_PixelFormat* pixel_format;

constexpr Uint32 kScreenWidth = 1920;
constexpr Uint32 kScreenHeight = 1080;
constexpr Uint32 kSimulationWidth = 512;
constexpr Uint32 kSimulationHeight = 512;
constexpr Uint32 kViewportWidth = 496;
constexpr Uint32 kViewportHeight = 279;
constexpr int kChunkSize = 64;

constexpr SDL_Rect kSimulationRect = {0, 0, kSimulationWidth, kSimulationHeight};
constexpr SDL_Rect kViewportRect = {0, 0, kViewportWidth, kViewportHeight};
constexpr SDL_Rect kScreenRect = {0, 0, kScreenWidth, kScreenHeight};
constexpr SDL_Rect kUIRect = {kScreenWidth-((kScreenWidth >> 4) << 2), 0 , (kScreenWidth >> 4) << 2, kScreenHeight};

constexpr char* kFontFilePath = "Assets/joystix-monospace.ttf";

constexpr Uint16 kMinDrawRadius = 0;
constexpr Uint16 kMaxDrawRadius = 75;

constexpr SDL_Color kCursorColor = {255, 255, 255, 255};
constexpr SDL_Color kUIPanelColor = {0, 0, 0, 255};

constexpr SDL_PixelFormatEnum kPixelFormat = SDL_PIXELFORMAT_ARGB8888;

constexpr Uint8 kButtonsInRow = 3;
constexpr float kButtonMargin = 0.05f;

constexpr SDL_Color kTextColor = {255, 255, 255, 255};

#endif /* Global_hpp */
