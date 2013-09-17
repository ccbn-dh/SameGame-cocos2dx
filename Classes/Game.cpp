#include "Game.h"
#include "cocos2d.h"

Game::Game()
{
    field = new Field();
    lastNumber = 0;
    
    filledBlocks = new bool*[FIELD_WIDTH];
    deletableBlocks = new bool*[FIELD_WIDTH];
    for (int x = 0; x < FIELD_WIDTH; x++) {
        filledBlocks[x] = new bool[FIELD_HEIGHT];
        deletableBlocks[x] = new bool[FIELD_HEIGHT];
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            filledBlocks[x][y] = false;
            deletableBlocks[x][y] = false;
        }
    }
}

Game::~Game()
{
    delete field; field = NULL;
    
    for (int x = 0; x < FIELD_WIDTH; x++) {
        delete filledBlocks[x]; filledBlocks[x] = NULL;
        delete deletableBlocks[x]; deletableBlocks[x] = NULL;
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

void Game::selectDeletable(int posX, int posY)
{
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            deletableBlocks[x][y] = false;
        }
    }
    Block* b = field->getBlocks()[posX][posY];
    execDeletableCheck(b->getColor(), posX, posY);
}

void Game::execDeletableCheck(int color, int x, int y)
{
    CCLOG("[execDeletableCheck] color:%d x:%d y:%d", color, x, y);
    
    // already checked
    if (deletableBlocks[x][y]) return;
    
    // another color
    if (field->getBlocks()[x][y]->getColor() != color) return;
    
    // be checked
    deletableBlocks[x][y] = true;

    // up
    if (y + 1 < FIELD_HEIGHT) execDeletableCheck(color, x, y + 1);
    // down
    if (y - 1 >= 0)           execDeletableCheck(color, x, y - 1);
    // left
    if (x - 1 >= 0)           execDeletableCheck(color, x - 1, y);
    // right
    if (x + 1 < FIELD_WIDTH)  execDeletableCheck(color, x + 1, y);
}

void Game::deleteDeletable()
{
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            if (deletableBlocks[x][y]) {
                delete field->getBlocks()[x][y];
                field->getBlocks()[x][y] = NULL;
            }
            deletableBlocks[x][y] = false;
        }
    }
}

void Game::fillBlocks()
{
    Block*** b = field->getBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            filledBlocks[x][y] = false;
            if (b[x][y] == NULL) {
                lastNumber++;
                b[x][y] = new Block(lastNumber, rand() % Block::kColor_Last);
                filledBlocks[x][y] = true;
            }
        }
    }
}

void Game::dropBlocks()
{
    Block*** b = field->getBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            if (b[x][y] == NULL) {
                for (int posY = y; posY + 1 < FIELD_HEIGHT; posY++) {
                    if (b[x][posY + 1] != NULL) {
                        b[x][posY] = b[x][posY + 1];
                        b[x][posY + 1] = NULL;
                    }
                }
            }
        }
    }
}
