//
//  engine.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 01/07/22.
//

#include "engine.h"

Engine::Engine(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
        printf("Error: %s\n", SDL_GetError());
    }
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto width = DM.w;
    auto height = DM.h;
    window_ = SDL_CreateWindow("MagiPixelEngine", 0, 0, width, height, 0);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == NULL){
        SDL_Log("Error creating SDL_Renderer!");
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer_Init(renderer_);
    show_demo_window = true;
    show_another_window = true;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    is_running_ = true;
}

void Engine::Clear(){
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Engine::HandleEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            is_running_ = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window_))
            is_running_ = false;
    }
}

void Engine::ShowAppMainMenuBar(){
    if (ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("File")){
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")){
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Engine::Update(){
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    ImGui::BeginMainMenuBar();
    ImGui::EndMainMenuBar();

    ShowAppMainMenuBar();
    Hierarchy::Instance()->Update();
    Viewer::Instance()->Update();
    Inspector::Instance()->Update();
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    
//    const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
//    static int item_current_idx = 0; // Here we store our selection data as an index.
//    // Custom size: use all width, 5 items tall
//    ImGui::Text("Hierarchy");
//    if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
//    {
//        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
//        {
//            const bool is_selected = (item_current_idx == n);
//            if (ImGui::Selectable(items[n], is_selected))
//                item_current_idx = n;
//
//            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
//            if (is_selected)
//                ImGui::SetItemDefaultFocus();
//        }
//        ImGui::EndListBox();
//    }
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }


}

void Engine::Render(){
    ImGui::Render();
    SDL_SetRenderDrawColor(renderer_, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer_);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer_);
}

bool Engine::Running(){
    return is_running_;
}
