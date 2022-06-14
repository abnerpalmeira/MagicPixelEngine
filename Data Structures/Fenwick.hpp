//
//  Fenwick.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 03/06/22.
//

#ifndef Fenwick_hpp
#define Fenwick_hpp
#include <stdio.h>
#include <vector>

class Fenwick{
public:
    int height_,width_;
    std::vector<std::vector<int> > f;
    Fenwick(){}
    Fenwick(int width,int height);
    ~Fenwick();
    void Update(int x, int y, int delta);
    int getSum(int x, int y);
    int getSum(int a, int b, int d, int c);
};

#endif /* Fenwick_hpp */
