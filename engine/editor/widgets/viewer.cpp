//
//  view.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 02/07/22.
//

#pragma once

#include "imgui.h"

class Viewer{
public:
    static Viewer* Instance(){
        if(!ptr_instance_)
            ptr_instance_ = new Viewer;
        return ptr_instance_;
    }
    void Update();
private:
    Viewer() = default;
    Viewer(const Viewer&);
    Viewer& operator=(const Viewer&);
    ~Viewer();
    void MainWindow();
    static Viewer* ptr_instance_;
};
