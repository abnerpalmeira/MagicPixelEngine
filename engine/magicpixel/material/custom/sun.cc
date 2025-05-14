#include "magicpixel/material/custom/sun.h"
#include "magicpixel/material/custom/steam.h"
#include "magicpixel/material/custom/lava.h"
#include "magicpixel/material/custom/water.h"
#include "magicpixel/material/custom/rock.h"
#include "magicpixel/material/custom/sand.h"
#include "magicpixel/material/custom/wood.h"
#include "magicpixel/material/custom/oil.h"
#include "magicpixel/material/custom/ice.h"

// Fire-like colors: bright yellow core, orange middle, red outer
Color Sun::colors[3] = {Color(255, 255, 0, 255), Color(255, 165, 0, 255), Color(255, 0, 0, 255)};
Uint32 Sun::min_temperature = 250;
Uint32 Sun::max_temperature = 1000;  // Reduced from 5000
Uint32 Sun::default_ttl = 100;  // Reduced from 1000

Sun::Sun() {
    ttl_ = current_tick + default_ttl + Random::IntOnInterval(0, 20);
    material_ = MaterialType::SUN;
    temperature_ = max_temperature;
    color_ = Color::Interpolate(colors[0], colors[2], Random::DoubleOnInterval(0.0, 1));
}

void Sun::CreateFlameParticle(Buffer &buffer, int x, int y, int height) {
    if (height <= 0) return;
    
    // Create a flame particle that rises and fades
    int offset_x = Random::IntOnInterval(-1, 1);
    int offset_y = -1;  // Always move upward
    
    if (x + offset_x >= 0 && x + offset_x < kSimulationWidth && 
        y + offset_y >= 0 && y + offset_y < kSimulationHeight) {
        
        if (buffer.buffer_[x + offset_x][y + offset_y].Empty()) {
            buffer.buffer_[x + offset_x][y + offset_y].CreateMagicPixel(MaterialType::GAS);
            auto& particle = buffer.buffer_[x + offset_x][y + offset_y].magic_pixel_ptr_;
            
            // Color fades from yellow to red as it rises
            float height_factor = static_cast<float>(height) / FLAME_HEIGHT;
            particle->color_ = Color::Interpolate(colors[0], colors[2], height_factor);
            particle->ttl_ = current_tick + height * 10;  // Shorter lifetime for higher particles
            
            // Recursively create more particles with decreasing height
            if (Random::IntOnInterval(0, 2) == 0) {  // 33% chance to create another particle
                CreateFlameParticle(buffer, x + offset_x, y + offset_y, height - 1);
            }
        }
    }
}

void Sun::CreateSmoke(Buffer &buffer, int x, int y, const Color &color) {
    // Create smoke particles with the color of the vaporized material
    for (int i = 0; i < 2; i++) {  // Reduced from 3
        int offset_x = Random::IntOnInterval(-1, 1);  // Reduced spread
        int offset_y = Random::IntOnInterval(-1, 1);
        
        if (!buffer.IsCellEmpty(x + offset_x, y + offset_y)) {
            auto& pixel = buffer.buffer_[x + offset_x][y + offset_y].magic_pixel_ptr_;
            if (pixel->material_ == MaterialType::EMPTY) {
                auto steam = std::make_unique<Steam>();
                steam->color_ = Color(color.GetR(), color.GetG(), color.GetB(), 128);
                buffer.CreateMagicPixel(MaterialType::STEAM, x + offset_x, y + offset_y);
            }
        }
    }
}

void Sun::HeatSurroundings(Buffer &buffer, int x, int y) {
    // Heat up surrounding materials with reduced radius
    for (int offset_y = -HEAT_RADIUS; offset_y <= HEAT_RADIUS; offset_y++) {
        for (int offset_x = -HEAT_RADIUS; offset_x <= HEAT_RADIUS; offset_x++) {
            if (offset_x == 0 && offset_y == 0) continue;
            
            float distance = std::sqrt(offset_x * offset_x + offset_y * offset_y);
            if (distance <= HEAT_RADIUS && !buffer.IsCellEmpty(x + offset_x, y + offset_y)) {
                auto& pixel = buffer.buffer_[x + offset_x][y + offset_y].magic_pixel_ptr_;
                if (pixel->material_ != MaterialType::EMPTY) {
                    // Heat decreases with distance
                    float heat_factor = 1.0f - (distance / HEAT_RADIUS);
                    Uint32 heat_amount = static_cast<Uint32>(MAX_TEMPERATURE * heat_factor);
                    pixel->temperature_ = std::min(pixel->temperature_ + heat_amount, MAX_TEMPERATURE);
                }
            }
        }
    }
}

void Sun::TransformMaterial(Buffer &buffer, int x, int y) {
    // Check surrounding materials and transform them based on temperature
    for (int offset_y = -1; offset_y <= 1; offset_y++) {
        for (int offset_x = -1; offset_x <= 1; offset_x++) {
            if (offset_x == 0 && offset_y == 0) continue;
            
            if (!buffer.IsCellEmpty(x + offset_x, y + offset_y)) {
                auto& pixel = buffer.buffer_[x + offset_x][y + offset_y].magic_pixel_ptr_;
                Color original_color = pixel->color_;
                
                if (pixel->temperature_ >= VAPORIZATION_TEMPERATURE) {
                    // Vaporize the material and create colored gas
                    for (int i = 0; i < 4; i++) {  // Increased from 3 to 4 particles
                        int gas_x = x + offset_x + Random::IntOnInterval(-2, 2);  // Increased spread
                        int gas_y = y + offset_y + Random::IntOnInterval(-2, 2);
                        
                        if (gas_x >= 0 && gas_x < kSimulationWidth && 
                            gas_y >= 0 && gas_y < kSimulationHeight &&
                            buffer.buffer_[gas_x][gas_y].Empty()) {
                            
                            buffer.buffer_[gas_x][gas_y].CreateMagicPixel(MaterialType::GAS);
                            auto& gas = buffer.buffer_[gas_x][gas_y].magic_pixel_ptr_;
                            gas->color_ = Color(original_color.GetR(), original_color.GetG(), original_color.GetB(), 200);
                            gas->ttl_ = current_tick + Random::IntOnInterval(150, 300);  // Increased duration
                        }
                    }
                    buffer.RemoveMagicPixel(x + offset_x, y + offset_y);
                }
                else if (pixel->temperature_ >= MELTING_TEMPERATURE) {
                    // Melt the material and create colored gas
                    for (int i = 0; i < 2; i++) {
                        int gas_x = x + offset_x + Random::IntOnInterval(-1, 1);
                        int gas_y = y + offset_y + Random::IntOnInterval(-1, 1);
                        
                        if (gas_x >= 0 && gas_x < kSimulationWidth && 
                            gas_y >= 0 && gas_y < kSimulationHeight &&
                            buffer.buffer_[gas_x][gas_y].Empty()) {
                            
                            buffer.buffer_[gas_x][gas_y].CreateMagicPixel(MaterialType::GAS);
                            auto& gas = buffer.buffer_[gas_x][gas_y].magic_pixel_ptr_;
                            gas->color_ = Color(original_color.GetR(), original_color.GetG(), original_color.GetB(), 150);
                            gas->ttl_ = current_tick + Random::IntOnInterval(50, 100);  // Increased duration
                        }
                    }
                    
                    // Transform the material
                    switch (pixel->material_) {
                        case MaterialType::ROCK:
                            buffer.CreateMagicPixel(MaterialType::LAVA, x + offset_x, y + offset_y);
                            break;
                        case MaterialType::ICE:
                            buffer.CreateMagicPixel(MaterialType::WATER, x + offset_x, y + offset_y);
                            break;
                        case MaterialType::WOOD:
                            // Wood burns and creates smoke
                            CreateSmoke(buffer, x + offset_x, y + offset_y, Color(139, 69, 19, 255));
                            buffer.RemoveMagicPixel(x + offset_x, y + offset_y);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void Sun::Update(Buffer &buffer, int x, int y) {
    temperature_ = std::min(temperature_ + 5, max_temperature);  // Reduced temperature increase
    
    // Create flame particles
    if (Random::IntOnInterval(0, 2) == 0) {  // 33% chance each update
        CreateFlameParticle(buffer, x, y, FLAME_HEIGHT);
    }
    
    // Heat and transform surrounding materials
    HeatSurroundings(buffer, x, y);
    TransformMaterial(buffer, x, y);
    
    // Update color with more dynamic variation
    if (!Random::IntOnInterval(0, 2)) {  // 33% chance to change color
        color_ = Color::Interpolate(colors[0], colors[2], Random::DoubleOnInterval(0.0, 1));
    }
    
    buffer.buffer_[x][y].SetUpdateFlag();
} 