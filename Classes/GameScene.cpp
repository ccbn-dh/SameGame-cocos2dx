#include "GameScene.h"

using namespace cocos2d;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    initGame();
    
    return true;
}

void GameScene::initGame()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    game = new Game();
    
    game->fillBlocks();
    bool** filled = game->getFilledBlocks();
    
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            if (filled[x][y]) {
                Block* b = game->getField()->getBlocks()[x][y];
                
                CCLabelTTF* l = CCLabelTTF::create("■", "Arial", 24.0);
                l->setPosition(ccp(size.width * (0.32 + x * 0.04), size.height * (0.1 + y * 0.06)));
                l->setTag(b->getNumber());
                switch (b->getColor()) {
                    case Block::kColor_White:  l->setColor(ccc3(255, 255, 255)); break;
                    case Block::kColor_Red:    l->setColor(ccc3(255,   0,   0)); break;
                    case Block::kColor_Green:  l->setColor(ccc3(  0, 255,   0)); break;
                    case Block::kColor_Blue:   l->setColor(ccc3(  0,   0, 255)); break;
                    case Block::kColor_Yellow: l->setColor(ccc3(255, 255,   0)); break;
                    default: break;
                }
                this->addChild(l);
            }
        }
    }
}