#ifndef __SameGame__Field__
#define __SameGame__Field__

#include <iostream>
#include "Block.h"

class Field
{
private:
    Block*** blocks;
    
public:
    Field();
    ~Field();
    Block*** getBlocks();
};

#endif /* defined(__SameGame__Field__) */
