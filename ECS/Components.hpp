//
//  Components.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 08/06/22.
//
#pragma once
#ifndef Components_hpp
#define Components_hpp

#include "ECS.hpp"
#include "Vector2.hpp"

class Transform : public Component{
private:
     Vector2 position;
public:
    void Init() override{
        position = Vector2();
    }
};


#endif /* Components_hpp */
