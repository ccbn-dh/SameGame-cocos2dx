#ifndef __SameGame__GameScene__
#define __SameGame__GameScene__

#include "cocos2d.h"
#include "Game.h"
#include "Config.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
private:
    Game* game;
    void initGame();
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

    void deleteBlocks(int x, int y);
};

#endif /* defined(__SameGame__GameScene__) */
