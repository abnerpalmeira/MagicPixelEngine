//
//  Button.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "Global.hpp"

struct ButtonText{
    SDL_Rect rect_;
    std::string text_;
};

class ButtonGroup{
public:
    ButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text, TTF_Font *font_);
    SDL_Surface* ToSurface();
private:
    TTF_Font *font_;
    SDL_Rect rect_;
    std::vector<ButtonText> buttons_;
};

#endif /* Button_hpp */
