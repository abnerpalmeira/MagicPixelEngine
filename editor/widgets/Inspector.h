//
//  Inspector.hpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 02/07/22.
//

#pragma once

#include "imgui.h"

class Inspector{
public:
    static Inspector* Instance(){
        if(!ptr_instance_)
            ptr_instance_ = new Inspector;
        return ptr_instance_;
    }
    void Update();
private:
    Inspector() = default;
    Inspector(const Inspector&);
    Inspector& operator=(const Inspector&);
    ~Inspector();
    static Inspector* ptr_instance_;
};
