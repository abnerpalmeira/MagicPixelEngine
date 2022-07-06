//
//  inspector.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 02/07/22.
//

#include "inspector.h"

Inspector* Inspector::ptr_instance_ = nullptr;

void Inspector::Update(){
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x+1520, main_viewport->WorkPos.y));
    ImGui::SetNextWindowSize(ImVec2(480, 1080));
    ImGui::Begin("Inspector",nullptr,0);
    ImGui::End();
}
