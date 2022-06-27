//
//  Navigation.h
//  MagicPixelEngine
//
//  Created by Abner Palmeira on 27/06/22.
//

#pragma once

class Navigation{
public:
    static int dx[8];
    static int dy[8];
};

int Navigation::dx[8] = {0, 0, 1,-1,1,-1, 1,-1};
int Navigation::dy[8] = {1,-1, 0, 0,1, 1,-1,-1};
