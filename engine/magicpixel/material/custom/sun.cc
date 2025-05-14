#include "magicpixel/material/custom/sun.h"
#include "magicpixel/material/custom/steam.h"
#include "magicpixel/material/custom/lava.h"
#include "magicpixel/material/custom/water.h"
#include "magicpixel/material/custom/rock.h"
#include "magicpixel/material/custom/sand.h"
#include "magicpixel/material/custom/wood.h"
#include "magicpixel/material/custom/oil.h"
#include "magicpixel/material/custom/ice.h"

Color Sun::colors[3] = {Color(255, 255, 0, 255), Color(255, 165, 0, 255), Color(255, 0, 0, 255)};  // Bright yellow, orange, red
Uint32 Sun::min_temperature = 250;
Uint32 Sun::max_temperature = 5000;
Uint32 Sun::default_ttl = 1000;

Sun::Sun() {
    ttl_ = current_tick + default_ttl + Random::IntOnInterval(0, 20);
    material_ = MaterialType::SUN;
    temperature_ = max_temperature;
    color_ = Color::Interpolate(colors[0], colors[2], Random::DoubleOnInterval(0.0, 1));
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
    temperature_ = std::min(temperature_ + 10, max_temperature);
    for (int i = 0; i < 8; i++) {
        int a = x + Navigation::dx[i], b = y + Navigation::dy[i];
        if (a < 0 || b < 0 || a >= kSimulationWidth || b >= kSimulationHeight) continue;
        if (buffer.buffer_[a][b].Empty()) {
            int should_emit = Random::IntOnInterval(0, 10);
            if (should_emit <= 1) {
                buffer.buffer_[a][b].CreateMagicPixel(MaterialType::GAS);
                buffer.buffer_[a][b].magic_pixel_ptr_->color_ = color_;
                buffer.buffer_[a][b].magic_pixel_ptr_->ttl_ = current_tick + 20;
            } else if (should_emit == 3) {
                buffer.buffer_[a][b].CreateMagicPixel(MaterialType::GAS);
                buffer.buffer_[a][b].magic_pixel_ptr_->ttl_ = current_tick + 100;
            }
        } else if (buffer.buffer_[a][b].GetMaterial() != MaterialType::SUN) {
            buffer.buffer_[a][b].TransferHeat(temperature_);
            if (buffer.Ignites(a, b, temperature_)) {
                buffer.ReplacMagicPixel(MaterialType::FIRE, a, b);
            } else {
                buffer.ReplacMagicPixel(MaterialType::SUN, a, b);
            }
        }
    }
    if (!Random::IntOnInterval(0, 3)) {
        color_ = Color::Interpolate(colors[0], colors[2], Random::DoubleOnInterval(0.0, 1));
    }
    buffer.buffer_[x][y].SetUpdateFlag();
} 