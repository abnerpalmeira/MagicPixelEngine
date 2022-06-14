//
//  GameObject.hpp
//  MagicPixel
//
//  Created by Abner Palmeira on 01/06/22.
//

#ifndef GameObject_hpp
#define GameObject_hpp
#include <stdio.h>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_image/SDL_image.h"
#include "Simulation.hpp"

class GameObject{
public:
    GameObject();
//    ~GameObject();
    void Update();
    void Render();
    void InitializeTextureFromText();
    void changeTexture(Uint32 *_buffer, Uint32 _size);
    void changeText(std::string _text);
    int button_count_ = 0;
    float scale_ = 0;
    std::string *text_;
    Uint32 *draw_buffer_;
    SDL_Renderer *renderer_;
    SDL_Texture* object_texture_;
    TTF_Font *font_;
    SDL_Rect *rect_;
    SDL_Rect *src_ = nullptr;
    SDL_Rect *buttons_;
    Simulation *simulation_;
    bool isButtonClicked(const SDL_Point *_pos, Uint8 &_button) const;
    
    
private:
};

#endif /* GameObject_hpp */
