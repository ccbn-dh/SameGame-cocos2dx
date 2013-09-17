#include "Game.h"
#include "cocos2d.h"

Game::Game()
{
    field = new Field();
    lastNumber = 0;
    
    filledBlocks = new bool*[FIELD_HEIGHT];
    deletableBlocks = new bool*[FIELD_HEIGHT];
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        filledBlocks[i] = new bool[FIELD_WIDTH];
        deletableBlocks[i] = new bool[FIELD_WIDTH];
        for (int j = 0; j < FIELD_WIDTH; j++) {
            filledBlocks[i][j] = false;
            deletableBlocks[i][j] = false;
        }
    }
}

Game::~Game()
{
    delete field; field = NULL;
    
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        delete filledBlocks[i]; filledBlocks[i] = NULL;
        delete deletableBlocks[i]; deletableBlocks[i] = NULL;
    }
    delete filledBlocks; filledBlocks = NULL;
    delete deletableBlocks; deletableBlocks = NULL;
}

Field* Game::getField()
{
    return field;
}

int Game::getLastNumber()
{
    return lastNumber;
}

bool** Game::getFilledBlocks()
{
    return filledBlocks;
}

bool** Game::getDeletableBlocks()
{
    return deletableBlocks;
}

void Game::fillField()
{
    Block*** b = field->getBlocks();
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            filledBlocks[i][j] = false;
            if (b[i][j] == NULL) {
                lastNumber++;
                b[i][j] = new Block(lastNumber, rand() % Block::kColor_Last);
                filledBlocks[i][j] = true;
            }
        }
    }
}

void Game::selectDeletable(int x, int y)
{
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            deletableBlocks[i][j] = false;
        }
    }
    Block* b = field->getBlocks()[y][x];
    execDeletableCheck(b->getColor(), x, y);
}

void Game::execDeletableCheck(int color, int x, int y)
{
    CCLOG("[execDeletableCheck] color:%d x:%d y:%d", color, x, y);
    
    // already checked
    if (deletableBlocks[y][x]) return;
    CCLOG("==== 1");
    
    // another color
    if (field->getBlocks()[y][x]->getColor() != color) return;
    CCLOG("==== 2");
    
    // be checked
    deletableBlocks[y][x] = true;
    CCLOG("==== 3");

    // up
    if (y + 1 < FIELD_HEIGHT) execDeletableCheck(color, x, y + 1);
    // down
    if (y - 1 >= 0)           execDeletableCheck(color, x, y - 1);
    // left
    if (x - 1 >= 0)           execDeletableCheck(color, x - 1, y);
    // right
    if (x + 1 < FIELD_WIDTH)  execDeletableCheck(color, x + 1, y);
}
