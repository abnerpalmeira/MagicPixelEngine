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
    count_ = 0;
}

void Game::InitFont(){
    TTF_Init();
    font = TTF_OpenFont(kFontFilePath, 16);
}

void Game::CreateSimulation() {
    simulation_ = new Simulation();
}

void Game::CreatePerfomanceBar() {
    performance_bar_ = new UI(renderer_,{Helper::ScreenWidthPoint(1),0,Helper::ScreenWidthPoint(8), Helper::ScreenHeightPoint(1)},Color(128,128,128,0));
    performance_bar_->AddText({0,0,Helper::ScreenWidthPoint(8),Helper::ScreenHeightPoint(1)}, "Hello World!");
}

void Game::CreateViewPort() {
    viewport_ = new GameObject();
    viewport_->object_texture_ptr_ =  new Texture(renderer_,(float)kScreenWidth/kViewportWidth,kViewportRect);
    viewport_->object_texture_ptr_->SetTextureBlendMode(SDL_BLENDMODE_BLEND);
    viewport_->object_texture_ptr_->SetTextureAlphaMod(255);
    viewport_->draw_buffer_ = new Uint32[kViewportWidth*kViewportHeight];
}

void Game::CreateUI() {
    auto set_material = std::bind(&Game::SetMaterial,this,std::placeholders::_1);
    auto pause = std::bind(&Game::Pause,this,std::placeholders::_1);
    auto reset = std::bind(&Game::ResetSimulation,this,std::placeholders::_1);
    ui_ = new UI(renderer_,{Helper::ScreenWidthPoint(11),0,(int)kScreenWidth-Helper::ScreenWidthPoint(11), (int)kScreenHeight},Color(128,128,128,255));
    ui_->AddButtonGroup({0,0,Helper::ScreenWidthPoint(4),Helper::ScreenWidthPoint(1)}, {0,0,120,64},"Pause",pause);
    ui_->AddButtonGroup({0,Helper::ScreenHeightPoint(1),Helper::ScreenWidthPoint(4),Helper::ScreenWidthPoint(2)}, {0,0,120,64},"Reset",reset);
    ui_->AddButtonGroup({0,Helper::ScreenWidthPoint(2),Helper::ScreenWidthPoint(4),Helper::ScreenWidthPoint(5)}, {0,0,120,64},"Empty Rock Sand Water Steam Wood Fire",set_material);
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
    delta_time = (current_tick - last_tick) / 1000.0f;;
}

void Game::HandleEvents(){
    InputManager::Instance()->PreUpdate();
    while(SDL_PollEvent(&e_)){
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
    if(ui_mode_ && SDL_PointInRect(&cursor,&ui_->rect_)){
        SDL_ShowCursor(SDL_ENABLE);
        if(InputManager::Instance()->mouse_states_[SDL_BUTTON_LEFT] == InputManager::KeyState::DOWN) ui_->Click();
    }else if(SDL_PointInRect(&cursor, &kScreenRect)){
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
    if(InputManager::Instance()->key_states_.contains(SDLK_TAB)  && InputManager::Instance()->key_states_[SDLK_TAB] == InputManager::KeyState::JUSTDOWN){
        ui_mode_ = !ui_mode_;
    }
    if(InputManager::Instance()->key_states_.contains(SDLK_r)  && InputManager::Instance()->key_states_[SDLK_r] == InputManager::KeyState::JUSTDOWN){
        debug_mode_ = !debug_mode_;
    }
//    if(InputManager::Instance()->key_states_.find(SDLK_s) != InputManager::Instance()->key_states_.end() && (InputManager::Instance()->key_states_[SDLK_s] == InputManager::KeyState::DOWN || InputManager::Instance()->key_states_[SDLK_s] == InputManager::KeyState::JUSTDOWN)){
//        viewport_->object_texture_ptr_->rect_.y = std::clamp(viewport_->object_texture_ptr_->rect_.y+1,0,(int)kSimulationHeight-(int)kViewportHeight);
//    }
    if(!paused_) {
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
        stream << std::fixed << std::setprecision(2) << "Current: " << (1.0f / frame_time) << " fps Avg: " << (1000 / std::max<Uint32>(tick_count_/frame_count, 1)) << " fps";
        performance_bar_->text_.back().text_ = stream.str();
        performance_bar_->CreateTexture();
    }
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    viewport_->Render();
    performance_bar_->Render();
    if(ui_mode_) ui_->Render();
    if(debug_mode_){
        for(int i=0;i<64;i++){
            (*simulation_->chunks_ptr_)[i].Debug(renderer_,viewport_->object_texture_ptr_->GetScale());
        }
    }
    SDL_SetRenderDrawColor(renderer_, kCursorColor.r, kCursorColor.g, kCursorColor.b, kCursorColor.a);
    Graphics::DrawCircle(renderer_, &cursor, &kScreenRect, draw_radius_*viewport_->object_texture_ptr_->GetScale());
    SDL_RenderPresent(renderer_);
}

void Game::Clean(){
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
}

