#pragma once

#include "core/game_object.h"
#include "common/geometry/vector.h"
#include "core/input_manager.h"
#include "simulation/simulation.h"

class Character : public GameObject {
public:
    Character(SDL_Renderer* renderer, Simulation* simulation, int x, int y);
    ~Character();
    
    void Update() override;
    void Render() override;
    
    void Move(const Vector2& direction);
    void SetPosition(int x, int y);
    void InteractWithSimulation();
    
private:
    Vector2 position_;
    Vector2 velocity_;
    float move_speed_ = 2.0f;
    SDL_Rect collision_box_;
    bool is_moving_ = false;
    Simulation* simulation_;
}; 