#include "button_text.h"

ButtonText::ButtonText(SDL_Rect rect,Color background_color, Color text_color, std::string text, char *font_file_path, int size, std::function<void()> fn){
    rect_ = rect;
    background_color_ = background_color;
    text_ = Text(rect, text_color, text, font_file_path, size);
    surface_ = Surface();
}