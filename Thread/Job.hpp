//
//  Job.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 06/06/22.
//

#ifndef Job_hpp
#define Job_hpp

#include <stdio.h>
#include <functional>
#include "Chunk.hpp"
#include "MagicPixel.hpp"

class Job{
public:
    Chunk *chunk_;
    Job(){}
    Job(Chunk &chunk);
};

#endif /* Job_hpp */
