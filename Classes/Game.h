#ifndef __SameGame__Game__
#define __SameGame__Game__

#include <iostream>
#include "Field.h"
#include "Block.h"
#include "Config.h"

class Game
{
private:
    Field* field;
    int lastNumber;
    bool** filledBlocks;
    
public:
    Game();
    ~Game();
    
    Field* getField();
    int getLastNumber();
    bool** getFilledBlocks();
    
    void fillField();
};

#endif /* defined(__SameGame__Game__) */
