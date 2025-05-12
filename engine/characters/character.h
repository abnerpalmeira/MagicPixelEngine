#pragma once

#include "core/game_object.h" // Keep for potential future use, though texture is removed
#include "common/geometry/vector.h"
#include "core/input_manager.h"
#include "simulation/simulation.h"
#include "magicpixel/material/material_type.h" // Include MaterialType

class Character { // No longer inherits GameObject directly if no texture needed
public:
    // Constructor takes renderer for potential debug drawing, not texture
    Character(SDL_Renderer* renderer, Simulation* simulation, int x, int y, int width = 3, int height = 3);
    ~Character();

    void Update();
    void Render(SDL_Renderer* renderer); // Keep Render for potential debug overlays if needed

    void Move(const Vector2& direction);
    void SetPosition(int x, int y);
    void InteractWithSimulation(); // Example interaction

    Vector2 GetPosition() const { return position_; }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }

private:
    // Place/Remove character pixels from the simulation buffer
    void PlaceCharacterPixels();
    void RemoveCharacterPixels();
    // Check if the character can move to the target top-left position
    bool CanOccupy(const Vector2& target_pos);

    Vector2 position_; // Top-left grid cell coordinate
    Vector2 velocity_; // Stores intended movement for the frame
    float move_speed_ = 1.0f; // Move one grid cell per step for simplicity now
    int width_;           // Width in grid cells
    int height_;          // Height in grid cells
    bool is_moving_ = false;
    Simulation* simulation_;
    SDL_Renderer* renderer_; // Store renderer if needed for debug

    MaterialType character_material_ = MaterialType::STATIC; // Material used for the character's body
    // Note: No collision_box_ needed if we use cell-based collision
    // Note: No object_texture_ptr_
};