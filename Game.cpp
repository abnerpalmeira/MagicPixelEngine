//
//  Game.cpp
//  MagicPixel
//
//  Created by Abner Palmeira on 31/05/22.
//
#include "Game.hpp"

SDL_Renderer* Game::renderer_ = nullptr;

enum class ToolButton : Uint8 {
    PAUSE = 0,
    ERASE,
    RESET,
    TOTAL_BUTTONS
};
  
void Game::CreateSimulation() {
    simulation_ = new GameObject();
    simulation_->rect_ =  Helper::Init(0, 0, kSimulationWidth, kSimulationHeight);
    simulation_->simulation_ = new Simulation(kSimulationWidth, kSimulationHeight);
}

void Game::CreateViewPort() {
    viewport_ = new GameObject();
    viewport_->rect_ =  Helper::Init(0, 0, kViewportWidth, kViewportHeight);
    viewport_->object_texture_ = Texture::LoadTexture(renderer_,*viewport_->rect_);
    SDL_SetTextureBlendMode(viewport_->object_texture_, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(viewport_->object_texture_, 255);
    viewport_->renderer_ = renderer_;
    viewport_->scale_ = (float)kScreenWidth/kViewportWidth;
    viewport_->draw_buffer_ = new Uint32[kViewportWidth*kViewportHeight];
}

void Game::PerformanceBar() {
    performance_bar_ = new GameObject();
    performance_bar_->rect_ =  Helper::Init(0,0,0,0);
    performance_bar_->object_texture_ = Texture::LoadTexture(renderer_,*    performance_bar_->rect_);
    performance_bar_->renderer_ = renderer_;
    performance_bar_->font_ =  font_;
}

void Game::CreateToolUI() {
    tools_ui_ = new GameObject();
    tools_ui_->renderer_ = renderer_;
    int foo = (kScreenWidth >> 4) << 2;
    tools_ui_->rect_ =  Helper::Init(kScreenWidth-foo,0,foo, kScreenHeight);
    tools_ui_->font_ =  font_;
    tools_ui_->text_ =  new std::string("Pause Erase Reset ");
    tools_ui_->InitializeTextureFromText();
}

void Game::CreateMaterialUI() {
    material_ui_ = new GameObject();
    material_ui_->renderer_ = renderer_;
    int foo = (kScreenWidth >> 4) << 2;
    int bar = (kScreenHeight / 9);
    material_ui_->rect_ =  Helper::Init(kScreenWidth-foo,bar,foo,kScreenHeight-bar);
    material_ui_->font_ =  font_;
    material_ui_->text_ = new std::string("Rock Sand Water Fire Lava Oil Ice Gas Steam Wood Plasma ");
    material_ui_->InitializeTextureFromText();
}

void Game::ResetVariables() {
    tick_count_ = 0;
    draw_radius_ = 15;
    cursor_ = {0, 0};
    last_cursor_ = cursor_;
    material_ = MaterialType::SAND;
}

Game::Game(const char *title, int x, int y, int w, int h, bool fullscreen){
    Init(title,x,y,w,h,fullscreen);
    CreateSimulation();
    CreateViewPort();
    PerformanceBar();
    CreateToolUI();
    CreateMaterialUI();
    ResetVariables();
    IMG_Init(IMG_INIT_JPG);
    background = IMG_LoadTexture(renderer_, "Assets/background.jpg");
}

Game::~Game(){
    delete simulation_;
    delete [] viewport_->draw_buffer_;
    delete viewport_;
    delete tools_ui_;
    delete material_ui_;
}

void Game::Init(const char *title, int x, int y, int w, int h, bool fullscreen){
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return;
    std::cout << "Subsystem Initialised...." << std::endl;
    int flags = 0;
    if(fullscreen){
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    window_ = SDL_CreateWindow(title, x, y, w, h,flags);
    if(!window_) return;
    std::cout << "Window Created...." << std::endl;
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer_) return;
    std::cout << "Rendered Created...." << std::endl;
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    is_running_ = true;
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    TTF_Init();
    font_ = TTF_OpenFont(kFontFilePath, 16);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

void Game::KeyPressed(SDL_Event e) {
    switch(e.key.keysym.sym){
        case SDLK_ESCAPE:
            quit_ = true;
            break;
        case SDLK_TAB:
            toggle_ ^= true;
            break;
            
        case SDLK_SPACE:
            paused_ = !paused_;
            break;
        default:
            break;
    }
}

void Game::MousePressed(SDL_Event e) {
    if(e.button.button == SDL_BUTTON_LEFT){
        mbr_pressed_ = true;
        mbr_held_ = true;
    }
    else if(e.button.button == SDL_BUTTON_RIGHT){
        mbl_pressed_ = true;
        mbl_held_ = true;
    }
}

void Game::HandleEvents()
{
    current_tick = SDL_GetTicks();
    frame_count++;
    mbr_pressed_ = false;
    draw_rad_changed_ = false;
    delta_time = (current_tick - last_tick) / 1000.0f;;
    while(SDL_PollEvent(&e_)){
        switch (e_.type) {
            case SDL_QUIT:
                is_running_ = false;
                break;
            case SDL_KEYDOWN:
                KeyPressed(e_);
                break;
            case SDL_MOUSEMOTION:
                cursor_.x = e_.button.x;
                cursor_.y = e_.button.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                MousePressed(e_);
                break;
            case SDL_MOUSEBUTTONUP:
                if(e_.button.button == SDL_BUTTON_LEFT) mbr_held_ = false;
                else if(e_.button.button == SDL_BUTTON_RIGHT) mbl_held_ = false;
                break;
            case SDL_MOUSEWHEEL:
                draw_radius_ = std::clamp<Sint16>(draw_radius_ + e_.wheel.y,kMinDrawRadius,kMaxDrawRadius);
                draw_rad_changed_ = true;
                break;
            default:
                break;
        }
    }
}

void Game::Update(){
    Uint8 clicked;
    if(!toggle_ && SDL_PointInRect(&cursor_, &kUIRect)){
        SDL_ShowCursor(SDL_ENABLE);
        if(mbr_pressed_ && tools_ui_->isButtonClicked(&cursor_, clicked)){
            switch(static_cast<ToolButton>(clicked)){
            case ToolButton::PAUSE:
                paused_ = !paused_;
                break;

            case ToolButton::ERASE:
                material_ = MaterialType::EMPTY;
                break;

            case ToolButton::RESET:
                    simulation_->simulation_->Reset();
                break;
            }
        }
        else if(mbr_pressed_ && material_ui_->isButtonClicked(&cursor_, clicked)){
            material_ = static_cast<MaterialType>(clicked + 1);
        }
    }
    else if(SDL_PointInRect(&cursor_, &kScreenRect)){
        SDL_Point foo = cursor_;
        foo.x = foo.x/viewport_->scale_;
        foo.y = foo.y/viewport_->scale_;
        SDL_ShowCursor(SDL_DISABLE);
        if(mbr_held_) {
            simulation_->simulation_->SetCellInsideRadius(foo, draw_radius_, material_);
        }
        if(mbl_held_) { simulation_->simulation_->SetCellInsideRadius(cursor_, draw_radius_, material_,true); }
    }
    if(!paused_) { simulation_->simulation_->Update(); }
    last_cursor_ = cursor_;
    std::ostringstream stream;
    Uint32 last_update = SDL_GetTicks();
    float frame_time = (last_update - current_tick) / 1000.0f;
    tick_count_ += last_update - current_tick;
    if(count_++ == 60 || draw_rad_changed_){
        count_ = 0;
        stream << std::fixed << std::setprecision(2) << "Current: " << (1.0f / frame_time) << " fps Avg: " << (1000 / std::max<Uint32>(tick_count_/frame_count, 1)) << " fps Pen size: "  << (draw_radius_);
        std::string text = stream.str();
            performance_bar_->changeText(text);
    }
    for(int i=0;i<viewport_->rect_->w;i++){
        for(int j=0;j<viewport_->rect_->h;j++){
            int foo = i + j * kViewportWidth;
            int bar = i + j * kSimulationWidth;
            MagicPixel *current = simulation_->simulation_->buffer_[bar];
            viewport_->draw_buffer_[foo] = (current == nullptr) ? empty_pixel_value : current->color_.GetSDLMap();

        }
    }
    SDL_UpdateTexture(viewport_->object_texture_, nullptr, viewport_->draw_buffer_, (kViewportWidth) * sizeof(Uint32));
}

void Game::Render(){
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, background, NULL, NULL);
    viewport_->Render();
    performance_bar_->Render();
    for(int i=0;i<64;i++){
        simulation_->simulation_->chunk_[i].Debug(renderer_,viewport_->scale_);
    }
    if(!toggle_){
        SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer_, &kUIRect);
        tools_ui_->Render();
        material_ui_->Render();
    }
    Graphics::drawCircle(renderer_, &cursor_, &kScreenRect, draw_radius_*5);
    Graphics::setRenderColor(renderer_, &kCursorColor);
    SDL_RenderPresent(renderer_);
}

void Game::Clean(){
    delete simulation_;
    delete [] viewport_->draw_buffer_;
    delete viewport_;
    delete tools_ui_;
    delete material_ui_;
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

