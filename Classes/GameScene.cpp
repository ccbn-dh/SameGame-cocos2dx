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
    
    // touch enable
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
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

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    // タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            Block* b = game->getField()->getBlocks()[x][y];
            CCLabelTTF* l = (CCLabelTTF*)this->getChildByTag(b->getNumber());
            if (!l) continue;
            CCRect rect = l->boundingBox();
            if (rect.containsPoint(touchPoint)) {
                deleteBlocks(x, y);
                return;
            }
        }
    }
}

void GameScene::deleteBlocks(int x, int y)
{
    // 削除ブロック判定
    game->selectDeletable(x, y);
    
    // 表示側削除
    bool** deletable = game->getDeletableBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            if (deletable[x][y]) {
                Block* b = game->getField()->getBlocks()[x][y];
                this->removeChildByTag(b->getNumber());
            }
        }
    }
    
    // ロジック側削除
    game->deleteDeletable();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // ブロック落下
    game->dropBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            Block* b = game->getField()->getBlocks()[x][y];
            if (b != NULL) {
                CCLabelTTF* l = (CCLabelTTF*)this->getChildByTag(b->getNumber());
                CCMoveTo* action = CCMoveTo::create(0.2, ccp(size.width * (0.32 + x * 0.04), size.height * (0.1 + y * 0.06)));
                l->runAction(action);
            }
        }
    }
    
    // ブロック埋め合わせ
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
