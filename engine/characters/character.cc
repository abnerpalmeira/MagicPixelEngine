#include "characters/character.h"
#include "graphics/color.h" // Potentially for debug rendering
#include "core/global.h"   // For kSimulationWidth/Height
#include <algorithm>       // For std::clamp

Character::Character(SDL_Renderer* renderer, Simulation* simulation, int x, int y, int width, int height)
    : renderer_(renderer), simulation_(simulation), position_(x, y), width_(width), height_(height), velocity_(0, 0)
{
    // Ensure initial position is valid
    position_.x_ = std::clamp(position_.x_, 0, static_cast<int>(kSimulationWidth) - static_cast<int>(width_));
    position_.y_ = std::clamp(position_.y_, 0, static_cast<int>(kSimulationHeight) - static_cast<int>(height_));

    // Place the character in the simulation grid initially
    PlaceCharacterPixels();

    // No texture creation needed anymore
    // No separate collision box needed, collision is grid-based
}

Character::~Character() {
    // Ensure character pixels are removed from the grid when destroyed
    if (simulation_) {
        RemoveCharacterPixels();
    }
    // No texture to delete
}

void Character::PlaceCharacterPixels() {
    if (!simulation_) return;
    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            int sim_x = position_.x_ + i;
            int sim_y = position_.y_ + j;
            // Check boundaries
            if (sim_x >= 0 && sim_x < kSimulationWidth && sim_y >= 0 && sim_y < kSimulationHeight) {
                // Overwrite whatever is there with the character material
                simulation_->buffer_ptr_->ReplacMagicPixel(character_material_, sim_x, sim_y);
                // Optional: Customize the pixel further (e.g., color)
                // simulation_->buffer_ptr_->buffer_[sim_x][sim_y].magic_pixel_ptr_->color_ = Color(0, 255, 0, 255); // Example: Green
            }
        }
    }
}

void Character::RemoveCharacterPixels() {
    if (!simulation_) return;
    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            int sim_x = position_.x_ + i;
            int sim_y = position_.y_ + j;
            // Check boundaries and if the pixel is actually part of the character
            if (sim_x >= 0 && sim_x < kSimulationWidth && sim_y >= 0 && sim_y < kSimulationHeight) {
                 // Only remove if it's character material (avoid erasing unrelated pixels if logic gets complex)
                 if(simulation_->buffer_ptr_->GetMaterial(sim_x, sim_y) == character_material_){
                    simulation_->buffer_ptr_->RemoveMagicPixel(sim_x, sim_y);
                 }
            }
        }
    }
}

bool Character::CanOccupy(const Vector2& target_pos) {
    if (!simulation_) return true; // Or false, depending on desired behavior without simulation

    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            int sim_x = target_pos.x_ + i;
            int sim_y = target_pos.y_ + j;

            // Check grid boundaries
            if (sim_x < 0 || sim_x >= kSimulationWidth || sim_y < 0 || sim_y >= kSimulationHeight) {
                return false; // Cannot move outside bounds
            }

            MaterialType mat = simulation_->buffer_ptr_->GetMaterial(sim_x, sim_y);

            // Check if the cell is occupied by something other than EMPTY or the character itself
            if (mat != MaterialType::EMPTY && mat != character_material_) {
                 // Add more sophisticated checks here if needed (e.g., allow moving through WATER)
                 // For now, any non-empty, non-character pixel blocks movement.
                return false;
            }
        }
    }
    return true; // Path is clear
}


void Character::Update() {
    if (!simulation_) return;

    // --- Input Handling ---
    auto input = InputManager::Instance();
    Vector2 move_direction(0, 0);
    is_moving_ = false;

    // Use integer steps for grid movement
    if (input->key_states_[SDLK_UP] == InputManager::KeyState::DOWN || input->key_states_[SDLK_UP] == InputManager::KeyState::JUSTDOWN) {
        move_direction.y_ = -1;
        is_moving_ = true;
    }
    if (input->key_states_[SDLK_DOWN] == InputManager::KeyState::DOWN || input->key_states_[SDLK_DOWN] == InputManager::KeyState::JUSTDOWN) {
        move_direction.y_ = 1;
        is_moving_ = true;
    }
    if (input->key_states_[SDLK_LEFT] == InputManager::KeyState::DOWN || input->key_states_[SDLK_LEFT] == InputManager::KeyState::JUSTDOWN) {
        move_direction.x_ = -1;
        is_moving_ = true;
    }
    if (input->key_states_[SDLK_RIGHT] == InputManager::KeyState::DOWN || input->key_states_[SDLK_RIGHT] == InputManager::KeyState::JUSTDOWN) {
        move_direction.x_ = 1;
        is_moving_ = true;
    }

    // --- Interaction ---
    if (input->key_states_[SDLK_SPACE] == InputManager::KeyState::JUSTDOWN) {
         InteractWithSimulation();
    }


    // --- Movement and Collision ---
    velocity_ = Vector2(0, 0); // Reset velocity each frame before applying movement
    if (is_moving_) {
        // Calculate potential next position (top-left corner)
        // Using move_speed_ as step size (e.g., 1 cell per update)
        Vector2 next_position = position_ + move_direction * static_cast<int>(move_speed_);

        // Clamp next position to prevent going completely out of bounds initially
        next_position.x_ = std::clamp(next_position.x_, 0, static_cast<int>(kSimulationWidth) - static_cast<int>(width_));
        next_position.y_ = std::clamp(next_position.y_, 0, static_cast<int>(kSimulationHeight) - static_cast<int>(height_));


        // Check if the entire character area can occupy the next position
        if (CanOccupy(next_position)) {
            // Clear old pixels
            RemoveCharacterPixels();
            // Update position
            position_ = next_position;
            // Place new pixels
            PlaceCharacterPixels();
            // Set velocity for this frame (optional, mostly for state)
            velocity_ = move_direction * static_cast<int>(move_speed_);
        } else {
            // Blocked, velocity remains zero
             is_moving_ = false;
        }
    }

    // No texture position update needed
    // No separate collision box update needed
    // No loop treating character as a solid particle needed (it *is* particles now)
}

// Render is now mostly for debugging purposes if needed
void Character::Render(SDL_Renderer* renderer) {
    // Example Debug Render: Draw a box around the character's grid area
    if (renderer && simulation_) { // Check if renderer is valid
         SDL_FRect debug_rect = {
            (float)position_.x_ * (kScreenWidth / (float)kViewportWidth), // Scale to viewport coords
            (float)position_.y_ * (kScreenHeight / (float)kViewportHeight),// Scale to viewport coords
            (float)width_ * (kScreenWidth / (float)kViewportWidth),
            (float)height_* (kScreenHeight / (float)kViewportHeight)
        };
         SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100); // Semi-transparent green
         SDL_RenderDrawRectF(renderer, &debug_rect);
    }

    // No call to GameObject::Render() needed if it was just for the texture
}

// Move is less relevant now as movement is handled directly in Update based on input
// Kept signature but might not be used externally in the same way
void Character::Move(const Vector2& direction) {
   // This function might be refactored or removed if movement is fully handled in Update
   // For now, it could potentially set a target velocity, but Update handles the step-by-step check
   // velocity_ = direction * move_speed_; // This alone doesn't check collision or update pixels
}

void Character::SetPosition(int x, int y) {
    if (!simulation_) return;

    Vector2 new_pos(x, y);
    // Clamp to valid top-left positions
    new_pos.x_ = std::clamp(new_pos.x_, 0, static_cast<int>(kSimulationWidth) - static_cast<int>(width_));
    new_pos.y_ = std::clamp(new_pos.y_, 0, static_cast<int>(kSimulationHeight) - static_cast<int>(height_));

    // Check if the new position is different and valid
    if (new_pos != position_ /* && CanOccupy(new_pos) */) { // Add CanOccupy if teleporting should respect collision
        RemoveCharacterPixels(); // Remove from old location
        position_ = new_pos;     // Update internal position
        PlaceCharacterPixels();  // Place at new location
    } else if (new_pos != position_) {
         // Optional: Handle case where SetPosition targets an invalid spot
         // std::cout << "Cannot set position to occupied space." << std::endl;
    } else {
        // If setting to the same position, ensure pixels are correctly placed (e.g., on initialization)
        PlaceCharacterPixels();
    }

    // No texture or collision box updates needed here
}

void Character::InteractWithSimulation() {
    if (!simulation_) return;

    // Example: Place water in front of the character (relative to its center)
    int center_x = position_.x_ + width_ / 2;
    int center_y = position_.y_ + height_ / 2;

    // Determine "front" based on last move or default (e.g., right)
    // This requires storing facing direction if needed. Simple example: place below.
    SDL_Point target_point;
    target_point.x = center_x;
    target_point.y = center_y + height_ / 2 + 1; // Just below the character

    // Clamp target point
    target_point.x = std::clamp(target_point.x, 0, static_cast<int>(kSimulationWidth) - 1);
    target_point.y = std::clamp(target_point.y, 0, static_cast<int>(kSimulationHeight) - 1);


    // Use the simulation's function to affect the grid
    simulation_->SetCellInsideCircle(target_point, 2, MaterialType::WATER, false); // Use the circle function
    // Or set a single cell:
    // simulation_->SetCell(target_point, MaterialType::WATER, false);
}