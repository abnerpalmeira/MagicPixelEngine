//
//  view.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 02/07/22.
//

#include "viewer.h"

Viewer* Viewer::ptr_instance_ = nullptr;

void Viewer::MainWindow(){
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x+240, main_viewport->WorkPos.y));
    ImGui::SetNextWindowSize(ImVec2(1280, 750));
    ImGui::Begin("Viewer",nullptr,window_flags);
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("ViewerTab", tab_bar_flags)){
        if (ImGui::BeginTabItem("Simulation")){
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game")){
            ImGui::SameLine();
            ImGui::Button("Play");
            ImGui::SameLine();
            ImGui::Button("Stop");
            
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::Separator();
    ImGui::End();
}


void Viewer::Update(){
    MainWindow();
}
