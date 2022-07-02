//
//  Hierarchy.cpp
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 02/07/22.
//

#include "Hierarchy.h"

Hierarchy* Hierarchy::ptr_instance_ = nullptr;

void Hierarchy::Update(){
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
    ImGui::SetNextWindowSize(ImVec2(240, 1080));
    ImGui::Begin("Hierarchy",nullptr,window_flags);
    ImGui::End();
}
