//
//  global.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 03/06/22.
//

#pragma once
#include <random>
#include <thread>
#include <SDL.h>
#include <SDL_ttf.h>

extern Uint32 frame_count;
extern Uint32 current_tick;
extern Uint32 last_tick;
extern Uint32 kEmptyPixelValue;
extern float delta_time;
extern SDL_PixelFormat *pixel_format;
extern SDL_Point cursor;
extern TTF_Font *font;
extern thread_local std::mt19937 rng;

constexpr Uint32 kScreenWidth = 1920;
constexpr Uint32 kScreenHeight = 1080;
constexpr Uint32 kSimulationWidth = 512;
constexpr Uint32 kSimulationHeight = 512;
constexpr Uint32 kSimulationWidthPower2Expoent = 9;
constexpr Uint32 kViewportWidth = 496;
constexpr Uint32 kViewportHeight = 279;
constexpr Uint32 kMaxCell = kSimulationWidth*kSimulationHeight;
constexpr int kMaxChunk = 64;
constexpr int kChunkBatchSize = 16;
constexpr int kDx[8] = {0,1,-1,1,-1,1,-1};
constexpr int kDy[8] = {1,1,1,-1,-1,0,0};

constexpr SDL_Rect kSimulationRect = {0, 0, kSimulationWidth, kSimulationHeight};
constexpr SDL_Rect kViewportRect = {0, 0, kViewportWidth, kViewportHeight};
constexpr SDL_Rect kScreenRect = {0, 0, kScreenWidth, kScreenHeight};
constexpr SDL_Rect kUIRect = {kScreenWidth-((kScreenWidth >> 4) << 2), 0 , (kScreenWidth >> 4) << 2, kScreenHeight};

constexpr char const *kFontFilePath = "Assets/joystix-monospace.ttf";

constexpr Uint16 kMinDrawRadius = 0;
constexpr Uint16 kMaxDrawRadius = 75;

constexpr SDL_Color kCursorColor = {255, 255, 255, 255};
constexpr SDL_Color kUIPanelColor = {0, 0, 0, 255};

constexpr SDL_PixelFormatEnum kPixelFormat = SDL_PIXELFORMAT_ARGB8888;

constexpr Uint8 kButtonsInRow = 3;
constexpr float kButtonMargin = 0.05f;

constexpr SDL_Color kTextColor = {255, 255, 255, 255};
