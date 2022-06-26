//
//  GameObject.cpp
//  MagicPixel
//
//  Created by Abner Palmeira on 01/06/22.
//

#include "GameObject.hpp"

GameObject::GameObject(){}

void GameObject::Update(){}

void GameObject::Render(){
    if(object_texture_ptr_ != NULL) object_texture_ptr_->Render();
}
