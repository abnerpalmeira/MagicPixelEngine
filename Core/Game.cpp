//
//  Game.cpp
//  MagicPixel
//
//  Created by Abner Palmeira on 31/05/22.
//
#include "Game.hpp"

SDL_Renderer* Game::renderer_ = nullptr;

Game::Game(const char *title, int x, int y, int w, int h, bool fullscreen){
    Init(title,x,y,w,h);
    InitFont();
    CreateSimulation();
    CreatePerfomanceBar();
    CreateViewPort();
    CreateUI();
    ResetVariables();
}

Game::~Game(){
    delete simulation_;
    delete [] viewport_->draw_buffer_;
    delete viewport_;
    delete ui_;
    delete material_ui_;
    TTF_CloseFont(font);
}

void Game::Init(const char *title, int x, int y, int w, int h){
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow(title, x, y, w, h,SDL_WINDOW_MAXIMIZED);
    renderer_ = SDL_CreateRenderer(window_, -1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    is_running_ = true;
}

void Game::InitFont(){
    TTF_Init();
    font = TTF_OpenFont(kFontFilePath, 16);
}

void Game::CreateSimulation() {
    simulation_ = new Simulation(kSimulationWidth, kSimulationHeight);
}

void Game::CreatePerfomanceBar() {
    performance_bar_ = new UI(renderer_,{Helper::ScreenWidthPoint(1),0,Helper::ScreenWidthPoint(8), Helper::ScreenHeightPoint(1)},Color(128,128,128,0));
    performance_bar_->AddText({0,0,Helper::ScreenWidthPoint(8),Helper::ScreenHeightPoint(1)}, "Hello World!");
}

void Game::CreateViewPort() {
    viewport_ = new GameObject();
    viewport_->texture_ =  new Texture(renderer_,(float)kScreenWidth/kViewportWidth,kViewportRect);
    viewport_->texture_->SetTextureBlendMode(SDL_BLENDMODE_BLEND);
    viewport_->texture_->SetTextureAlphaMod(255);
    viewport_->draw_buffer_ = new Uint32[kViewportWidth*kViewportHeight];
}

void Game::CreateUI() {
    auto set_material = std::bind(&Game::SetMaterial,this,std::placeholders::_1);
    auto pause = std::bind(&Game::Pause,this,std::placeholders::_1);
    auto reset = std::bind(&Game::ResetSimulation,this,std::placeholders::_1);
    ui_ = new UI(renderer_,{Helper::ScreenWidthPoint(11),0,(int)kScreenWidth-Helper::ScreenWidthPoint(11), (int)kScreenHeight},Color(128,128,128,255));
    ui_->AddButtonGroup({0,0,Helper::ScreenWidthPoint(4),Helper::ScreenWidthPoint(1)}, {0,0,120,64},"Pause",pause);
    ui_->AddButtonGroup({0,Helper::ScreenHeightPoint(1),Helper::ScreenWidthPoint(4),Helper::ScreenWidthPoint(2)}, {0,0,120,64},"Reset",reset);
    ui_->AddButtonGroup({0,Helper::ScreenWidthPoint(2),Helper::ScreenWidthPoint(4),Helper::ScreenWidthPoint(5)}, {0,0,120,64},"Empty Rock Sand Water Fire Gas",set_material);
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
    input_manager.PreUpdate();
    current_tick = SDL_GetTicks();
    frame_count++;
    delta_time = (current_tick - last_tick) / 1000.0f;;
}

void Game::HandleEvents(){
    while(SDL_PollEvent(&e_)){
        switch (e_.type) {
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                input_manager.Handle(&e_);
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
    ui_->Update();
    if(SDL_PointInRect(&cursor,&ui_->rect_)){
        SDL_ShowCursor(SDL_ENABLE);
        if(input_manager.mouse_states_[SDL_BUTTON_LEFT] == InputManager::KeyState::DOWN) ui_->Click();
    }else if(SDL_PointInRect(&cursor, &kScreenRect)){
        SDL_ShowCursor(SDL_DISABLE);
        SDL_Point foo = cursor;
        foo.x = foo.x/viewport_->texture_->scale_;
        foo.y = foo.y/viewport_->texture_->scale_;
        if(input_manager.mouse_states_[SDL_BUTTON_LEFT] == InputManager::KeyState::DOWN){
            simulation_->SetCellInsideRadius(foo, draw_radius_, material_);
        }
        else if(input_manager.mouse_states_[SDL_BUTTON_RIGHT] == InputManager::KeyState::DOWN) {
            simulation_->SetCellInsideRadius(foo, draw_radius_, material_,true);
        }
    }
    if(!paused_) {
        simulation_->Update();
        for(int i=0;i<kViewportWidth;i++){
            for(int j=0;j<kViewportHeight;j++){
                int foo = i + j * kViewportWidth;
                int bar = i + j * kSimulationWidth;
                MagicPixel *current = simulation_->buffer_[bar];
                viewport_->draw_buffer_[foo] = (current == nullptr) ? empty_pixel_value : current->color_.GetSDLMap();
            }
        }
        SDL_UpdateTexture(viewport_->texture_->texture_, nullptr, viewport_->draw_buffer_, (kViewportWidth) * sizeof(Uint32));
    }
    LateUpdate();
}

void  Game::LateUpdate(){
    last_cursor_ = cursor;
    std::ostringstream stream;
    Uint32 last_update = SDL_GetTicks();
    last_tick = current_tick;
    float frame_time = (last_update - current_tick) / 1000.0f;
    tick_count_ += last_update - current_tick;
    if(count_++ == 60){
        count_ = 0;
        stream << std::fixed << std::setprecision(2) << "Current: " << (1.0f / frame_time) << " fps Avg: " << (1000 / std::max<Uint32>(tick_count_/frame_count, 1)) << " fps Draw radius: "  << (draw_radius_);
        performance_bar_->text_.back().text_ = stream.str();
        performance_bar_->CreateTexture();
    }
    
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    viewport_->Render();
    performance_bar_->Render();
    ui_->Render();
    if(true){
        for(int i=0;i<64;i++){
            simulation_->chunk_[i].Debug(renderer_,viewport_->texture_->GetScale());
        }
    }
    Graphics::setRenderColor(renderer_, &kCursorColor);
    Graphics::drawCircle(renderer_, &cursor, &kScreenRect, draw_radius_*viewport_->texture_->GetScale());
    SDL_RenderPresent(renderer_);
}

void Game::Clean(){
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

