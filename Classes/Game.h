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
    bool** deletableBlocks;
    
    void execDeletableCheck(int color, int x, int y);
    
public:
    Game();
    ~Game();
    
    Field* getField();
    int getLastNumber();
    bool** getFilledBlocks();
    bool** getDeletableBlocks();
    
    void selectDeletable(int x, int y);
    void deleteDeletable();
    
    void fillBlocks();    
    void dropBlocks();
};

#endif /* defined(__SameGame__Game__) */
