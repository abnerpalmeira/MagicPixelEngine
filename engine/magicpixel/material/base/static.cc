//
//  static.cc
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 28/06/22.
//

#include "magicpixel/material/base/static.h"

Static::Static() {
    color_ = Color(128, 128, 128, 255);
    material_ = MaterialType::STATIC;
}

void Static::Update(Buffer &buffer, int x, int y) {
    // Static objects don't move or change
    MagicPixel::Update(buffer, x, y);
}
