#include "magicpixel/material/custom/sun.h"
#include "magicpixel/material/custom/steam.h"
#include "magicpixel/material/custom/lava.h"
#include "magicpixel/material/custom/water.h"
#include "magicpixel/material/custom/rock.h"
#include "magicpixel/material/custom/sand.h"
#include "magicpixel/material/custom/wood.h"
#include "magicpixel/material/custom/oil.h"
#include "magicpixel/material/custom/ice.h"

Sun::Sun() {
    color_ = Color(255, 255, 0, 255);  // Bright yellow
    material_ = MaterialType::SUN;
    temperature_ = MAX_TEMPERATURE;
    ttl_ = current_tick + DEFAULT_TTL;
    original_color_ = color_;
}

void Sun::CreateSmoke(Buffer &buffer, int x, int y, const Color &color) {
    // Create smoke particles with the color of the vaporized material
    for (int i = 0; i < 3; i++) {
        int offset_x = Random::IntOnInterval(-2, 2);
        int offset_y = Random::IntOnInterval(-2, 2);
        
        if (!buffer.IsCellEmpty(x + offset_x, y + offset_y)) {
            auto& pixel = buffer.buffer_[x + offset_x][y + offset_y].magic_pixel_ptr_;
            if (pixel->material_ == MaterialType::EMPTY) {
                auto steam = std::make_unique<Steam>();
                steam->color_ = Color(color.GetR(), color.GetG(), color.GetB(), 128);  // Make it semi-transparent
                buffer.CreateMagicPixel(MaterialType::STEAM, x + offset_x, y + offset_y);
            }
        }
    }
}

void Sun::HeatSurroundings(Buffer &buffer, int x, int y) {
    // Heat up surrounding materials
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
                    // Vaporize the material
                    CreateSmoke(buffer, x + offset_x, y + offset_y, original_color);
                    buffer.RemoveMagicPixel(x + offset_x, y + offset_y);
                }
                else if (pixel->temperature_ >= MELTING_TEMPERATURE) {
                    // Melt the material
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
    // Update the sun's color based on temperature
    float temperature_factor = static_cast<float>(temperature_) / MAX_TEMPERATURE;
    color_ = Color(
        static_cast<Uint8>(255 * temperature_factor),
        static_cast<Uint8>(255 * (1.0f - temperature_factor * 0.5f)),
        static_cast<Uint8>(255 * (1.0f - temperature_factor)),
        255
    );
    
    // Heat surrounding materials
    HeatSurroundings(buffer, x, y);
    
    // Transform materials based on temperature
    TransformMaterial(buffer, x, y);
    
    // Check if the sun should disappear
    if (current_tick >= ttl_) {
        buffer.RemoveMagicPixel(x, y);
    }
} 