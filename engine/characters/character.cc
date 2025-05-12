#include "characters/character.h"
#include "graphics/color.h"

Character::Character(SDL_Renderer* renderer, Simulation* simulation, int x, int y) {
    renderer_ = renderer;
    simulation_ = simulation;
    position_ = Vector2(x, y);
    velocity_ = Vector2(0, 0);
    
    // Create a simple colored rectangle as the character's texture
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, 255, 0, 0, 255)); // Red color, fully opaque
    
    object_texture_ptr_ = new Texture(renderer, 1.0f, {x, y, 32, 32});
    object_texture_ptr_->UpdateTexture(surface->pixels);
    
    SDL_FreeSurface(surface);
    
    // Set up collision box
    collision_box_ = {x, y, 32, 32};
}

Character::~Character() {
    if (object_texture_ptr_) {
        delete object_texture_ptr_;
    }
}

void Character::Update() {
    // Handle input
    auto input = InputManager::Instance();
    
    Vector2 move_direction(0, 0);
    is_moving_ = false;
    
    if (input->key_states_[SDLK_UP] == InputManager::KeyState::DOWN) {
        move_direction.y_ = -1;
        is_moving_ = true;
    }
    if (input->key_states_[SDLK_DOWN] == InputManager::KeyState::DOWN) {
        move_direction.y_ = 1;
        is_moving_ = true;
    }
    if (input->key_states_[SDLK_LEFT] == InputManager::KeyState::DOWN) {
        move_direction.x_ = -1;
        is_moving_ = true;
    }
    if (input->key_states_[SDLK_RIGHT] == InputManager::KeyState::DOWN) {
        move_direction.x_ = 1;
        is_moving_ = true;
    }
    
    // Collision detection with simulation
    Vector2 next_position = position_;
    if (is_moving_) {
        next_position += move_direction * move_speed_;
        // Check the cell at the next position
        int cell_x = static_cast<int>(next_position.x_);
        int cell_y = static_cast<int>(next_position.y_);
        if (simulation_ && cell_x >= 0 && cell_x < kSimulationWidth && cell_y >= 0 && cell_y < kSimulationHeight) {
            MaterialType mat = simulation_->buffer_ptr_->GetMaterial(cell_x, cell_y);
            if (mat == MaterialType::EMPTY || mat == MaterialType::WATER || mat == MaterialType::STEAM || mat == MaterialType::FIRE || mat == MaterialType::GAS || mat == MaterialType::LIQUID) {
                Move(move_direction);
            } else {
                velocity_ = Vector2(0, 0); // Block movement
                is_moving_ = false;
            }
        } else {
            Move(move_direction);
        }
    } else {
        velocity_ = Vector2(0, 0);  // Stop movement when no keys are pressed
    }
    
    // Update position
    position_ += velocity_;
    
    // Update texture position
    if (object_texture_ptr_) {
        object_texture_ptr_->rect_.x = position_.x_;
        object_texture_ptr_->rect_.y = position_.y_;
    }
    
    // Update collision box
    collision_box_.x = position_.x_;
    collision_box_.y = position_.y_;
    
    // Treat character as a solid particle
    if (simulation_) {
        for (int i = 0; i < kSimulationWidth; i++) {
            for (int j = 0; j < kSimulationHeight; j++) {
                if (simulation_->buffer_ptr_->GetMaterial(i, j) != MaterialType::EMPTY) {
                    SDL_Rect particle_rect = {i, j, 1, 1};
                    if (SDL_HasIntersection(&collision_box_, &particle_rect)) {
                        // Block the particle (treat character as solid)
                        // Optionally, you can add logic here to push the particle or change its behavior
                    }
                }
            }
        }
    }
}

void Character::Render() {
    GameObject::Render();
}

void Character::Move(const Vector2& direction) {
    velocity_ = direction * move_speed_;
}

void Character::SetPosition(int x, int y) {
    position_ = Vector2(x, y);
    if (object_texture_ptr_) {
        object_texture_ptr_->rect_.x = x;
        object_texture_ptr_->rect_.y = y;
    }
    collision_box_.x = x;
    collision_box_.y = y;
}

void Character::InteractWithSimulation() {
    if (!simulation_) return;
    
    // Convert character position to simulation coordinates
    SDL_Point sim_point;
    sim_point.x = position_.x_;
    sim_point.y = position_.y_;
    
    // Interact with the simulation by setting cells around the character
    simulation_->SetCellInsideCircle(sim_point, 2, MaterialType::WATER, true);
} 