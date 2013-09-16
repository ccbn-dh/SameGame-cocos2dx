#ifndef __SameGame__Block__
#define __SameGame__Block__

#include <iostream>

class Block
{
private:
    int number;
    int color;
    
public:
    Block(int number, int color);
    
    enum kColor
    {
        kColor_White,
        kColor_Red,
        kColor_Blue,
        kColor_Green,
        kColor_Yellow,
        kColor_Last,
    };
    
    int getNumber();
    int getColor();
};

#endif /* defined(__SameGame__Block__) */
