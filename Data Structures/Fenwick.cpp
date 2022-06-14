//
//  Fenwick.cpp
//  2D Sand
//
//  Created by Abner Palmeira on 03/06/22.
//

#include "Fenwick.hpp"

Fenwick::Fenwick(int width,int height){
    width_ = width;
    height_ = height;
    f = std::vector<std::vector<int> >(width,std::vector<int>(height,0));
}

void Fenwick::Update(int x, int y, int delta){
    for (int i = x; i < width_; i = i | (i + 1))
        for (int j = y; j < height_; j = j | (j + 1))
            f[i][j] += delta;
}

int Fenwick::getSum(int x, int y){
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                result += f[i][j];
    return result;
}

int Fenwick::getSum(int a, int b, int c, int d){
    return getSum(c, d) - getSum(c, b - 1) - getSum(a - 1, d) + getSum(a - 1, b - 1);
}
