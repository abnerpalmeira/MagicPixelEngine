//
//  Hierarchy.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 02/07/22.
//

#pragma once

#include "imgui.h"

class Hierarchy{
public:
    static Hierarchy* Instance(){
        if(!ptr_instance_)
            ptr_instance_ = new Hierarchy;
        return ptr_instance_;
    }
    void Update();
private:
    Hierarchy() = default;
    Hierarchy(const Hierarchy&);
    Hierarchy& operator=(const Hierarchy&);
    ~Hierarchy();
    static Hierarchy* ptr_instance_;
};
