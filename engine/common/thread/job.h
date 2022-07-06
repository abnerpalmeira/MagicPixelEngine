//
//  job.h
//  2D Sand
//
//  Created by Abner Palmeira on 06/06/22.
//

#pragma once

#include <stdio.h>
#include <functional>
#include "chunk.h"
#include "magic_pixel.h"

class Job{
public:
    Chunk *chunk_;
    Job(){}
    Job(Chunk &chunk);
};

#endif /* Job_hpp */
