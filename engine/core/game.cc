//
//  game.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 31/05/22.
//
#include "game.h"

SDL_Renderer* Game::renderer_ = nullptr;

Game::Game(const char *title, int x, int y, int w, int h, bool fullscreen){
    Init(title,x,y,w,h);
    InitFont();
    CreateSimulation();
    CreateViewPort();
    ResetVariables();
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer_Init(renderer_);
}

Game::~Game(){
    delete simulation_;
    delete [] viewport_->draw_buffer_;
    delete viewport_;
    delete ui_;
    delete material_ui_;
    TTF_CloseFont(font);
    
    // Cleanup ImGui
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Game::Init(const char *title, int x, int y, int w, int h){
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow(title, x, y, w, h,SDL_WINDOW_MAXIMIZED);
    renderer_ = SDL_CreateRenderer(window_, -1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    is_running_ = true;
    count_ = 0;
}

void Game::InitFont(){
    TTF_Init();
    font = TTF_OpenFont(kFontFilePath, 16);
}

void Game::CreateSimulation() {
    simulation_ = new Simulation();
}

void Game::CreateViewPort() {
    viewport_ = new GameObject();
    viewport_->object_texture_ptr_ =  new Texture(renderer_,(float)kScreenWidth/kViewportWidth,kViewportRect);
    viewport_->object_texture_ptr_->SetTextureBlendMode(SDL_BLENDMODE_BLEND);
    viewport_->object_texture_ptr_->SetTextureAlphaMod(255);
    viewport_->draw_buffer_ = new Uint32[kViewportWidth*kViewportHeight];
}

void Game::ShowMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Reset Simulation", "R")) {
                ResetSimulation(0);
            }
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                is_running_ = false;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Material Panel", NULL, &show_material_panel_);
            ImGui::MenuItem("Performance Panel", NULL, &show_performance_panel_);
            ImGui::MenuItem("Debug Panel", NULL, &show_debug_panel_);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Game::ShowMaterialPanel() {
    if (!show_material_panel_) return;
    
    ImGui::Begin("Materials", &show_material_panel_);
    
    if (ImGui::Button(paused_ ? "Resume" : "Pause")) {
        Pause(0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        ResetSimulation(0);
    }
    
    ImGui::Separator();
    
    const char* materials[] = {
        "Empty","Rock","Sand","Water","Steam","Wood","Fire",
        "Gas","Liquid","Solid","Static","Oil","Ice","Lava"
    };
    for (int i = 0; i < IM_ARRAYSIZE(materials); i++) {
        if (ImGui::Selectable(materials[i], material_ == static_cast<MaterialType>(i))) {
            SetMaterial(i);
        }
    }
    
    ImGui::Separator();
    ImGui::Text("Draw Radius: %d", draw_radius_);
    ImGui::SliderInt("##radius", (int*)&draw_radius_, kMinDrawRadius, kMaxDrawRadius);
    
    ImGui::End();
}

void Game::ShowPerformancePanel() {
    if (!show_performance_panel_) return;
    
    ImGui::Begin("Performance", &show_performance_panel_);
    
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Draw Calls: %d", count_);
    
    ImGui::End();
}

void Game::ShowDebugPanel() {
    if (!show_debug_panel_) return;
    
    ImGui::Begin("Debug", &show_debug_panel_);
    
    ImGui::Checkbox("Debug Mode", &debug_mode_);
    ImGui::Text("Cursor Position: (%d, %d)", cursor.x, cursor.y);
    ImGui::Text("Viewport Scale: %.2f", viewport_->object_texture_ptr_->GetScale());
    
    ImGui::End();
}

bool Game::Running(){
    return is_running_;
}

void Game::SetMaterial(int material){
    material_ = static_cast<MaterialType>(material);
}

void Game::Pause(int x){
    paused_ = !paused_;
}

void Game::ResetSimulation(int x){
    simulation_->Reset();
}

void Game::ResetVariables() {
    tick_count_ = 0;
    draw_radius_ = 15;
    material_ = MaterialType::ROCK;
}

void Game::PreUpdate(){
    current_tick = SDL_GetTicks();
    frame_count++;
    delta_time = (current_tick - last_tick) / 1000.0f;
}

void Game::HandleEvents(){
    InputManager::Instance()->PreUpdate();
    while(SDL_PollEvent(&e_)){
        ImGui_ImplSDL2_ProcessEvent(&e_);
        switch (e_.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                InputManager::Instance()->Handle(&e_);
                break;
            case SDL_MOUSEWHEEL:
                draw_radius_ = std::clamp<Sint16>(draw_radius_ + e_.wheel.y,kMinDrawRadius,kMaxDrawRadius);
                break;
            case SDL_QUIT:
                is_running_ = false;
                break;
            case SDL_MOUSEMOTION:
                cursor.x = e_.button.x;
                cursor.y = e_.button.y;
                break;
            default:
                break;
        }
    }
}

void Game::Update(){
    PreUpdate();
    
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    ShowMainMenuBar();
    ShowMaterialPanel();
    ShowPerformancePanel();
    ShowDebugPanel();
    
    if(!paused_) {
        if(SDL_PointInRect(&cursor, &kScreenRect)){
            SDL_ShowCursor(SDL_DISABLE);
            SDL_Point foo = cursor;
            foo.x = foo.x/viewport_->object_texture_ptr_->scale_;
            foo.y = foo.y/viewport_->object_texture_ptr_->scale_;
            if(InputManager::Instance()->mouse_states_[SDL_BUTTON_LEFT] == InputManager::KeyState::DOWN){
                simulation_->SetCellInsideCircle(foo, draw_radius_, material_);
            }
            else if(InputManager::Instance()->mouse_states_[SDL_BUTTON_RIGHT] == InputManager::KeyState::DOWN) {
                simulation_->SetCellInsideCircle(foo, draw_radius_, material_,true);
            }
        }
        
        // Update simulation and viewport
        int pitch = (kViewportWidth) * 8;
        SDL_LockTexture(viewport_->object_texture_ptr_->texture_, nullptr, (void**) &viewport_->draw_buffer_, &pitch);
        simulation_->Update();
        for(int i=0;i<kViewportWidth;i++){
            for(int j=0;j<kViewportHeight;j++){
                int foo = i + j * kViewportWidth;
                viewport_->draw_buffer_[foo] = simulation_->buffer_ptr_->GetCellColor(i, j);
            }
        }
        SDL_UnlockTexture(viewport_->object_texture_ptr_->texture_);
    }
    
    if(InputManager::Instance()->key_states_.contains(SDLK_TAB) && InputManager::Instance()->key_states_[SDLK_TAB] == InputManager::KeyState::JUSTDOWN){
        ui_mode_ = !ui_mode_;
    }
    
    // Update last tick for delta time calculation
    last_tick = current_tick;
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    
    viewport_->Render();
    
    if(debug_mode_){
        for(int i=0;i<64;i++){
            (*simulation_->chunks_ptr_)[i].Debug(renderer_,viewport_->object_texture_ptr_->GetScale());
        }
    }
    
    SDL_SetRenderDrawColor(renderer_, kCursorColor.r, kCursorColor.g, kCursorColor.b, kCursorColor.a);
    Graphics::DrawCircle(renderer_, &cursor, &kScreenRect, draw_radius_*viewport_->object_texture_ptr_->GetScale());
    
    // Render ImGui
    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    
    SDL_RenderPresent(renderer_);
}

void Game::Clean(){
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
}

