//
//  button.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 17/06/22.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <SDL.h>
#include <SDL.h>
#include "core/global.h"
#include"graphics/color.h"


template < class T, class... Args >
class Button{
public:
    typedef T(*EventFuntion)(Args...);
    Button( EventFuntion func_ptr ) : func_ptr_( func_ptr ){}
    ~Button(){ func_ptr_ = NULL; }
    void operator() ( Args&... args ) const{
        (func_ptr_)(args...);
    }
private:
    EventFuntion func_ptr_;
};

struct ButtonText{
    SDL_Rect rect_;
    std::string text_;
};

class ButtonGroup{
public:
    ButtonGroup(SDL_Rect group_rect,SDL_Rect button_rect, std::string text,std::function<void(int)> fn);
    ~ButtonGroup();
    SDL_Surface* ToSurface();
    SDL_Rect rect_;
    void Click(SDL_Point click_position);
private:
    std::function<void(int)> fn_;
    std::vector<ButtonText> buttons_;
};