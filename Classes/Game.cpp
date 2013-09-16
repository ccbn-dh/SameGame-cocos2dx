#include "Game.h"

Game::Game()
{
    field = new Field();
    lastNumber = 0;
    
    filledBlocks = new bool*[FIELD_HEIGHT];
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        filledBlocks[i] = new bool[FIELD_WIDTH];
        for (int j = 0; j < FIELD_WIDTH; j++) {
            filledBlocks[i][j] = false;
        }
    }
}

Game::~Game()
{
    delete field; field = NULL;
    
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        delete filledBlocks[i]; filledBlocks[i] = NULL;
    }
    delete filledBlocks; filledBlocks = NULL;
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