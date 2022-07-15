//
//  entity.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 01/06/22.
//

#include "camera.h"

Camera::Camera(float scale, SDL_Rect rect){
    texture_ = Texture(scale,rect);
    texture_.SetTextureBlendMode(SDL_BLENDMODE_BLEND);
    texture_.SetTextureAlphaMod(255);
    draw_buffer_ = new Uint32[rect.h*rect.w];
}

Camera::~Camera(){
    delete draw_buffer_;
}

bool Camera::IsClicked(){
    if(enabled_ && SDL_PointInRect(&InputManager::Instance()->mouse_position_, &rect_)){
        KeyState aux = &InputManager::Instance()->GetButton[SDL_KEY]
    }
    return false;
}

void Camera::Click(){
    
}

void Camera::Update(){

}

void Camera::Render(){
    texture_.Render();
}