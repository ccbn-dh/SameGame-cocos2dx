#import "GameTest.h"
#import "Game.h"
#import "Config.h"

@implementation GameTest

- (void)testGame
{
    Game* g = new Game();
    
    STAssertTrue(g->getField()->getBlocks()[FIELD_HEIGHT-1][FIELD_WIDTH-1] == NULL, @"before fill field");
    STAssertTrue(g->getFilledBlocks()[FIELD_HEIGHT-1][FIELD_WIDTH-1] == false, @"before fill field");
    
    g->fillField();
    
    STAssertTrue(g->getField()->getBlocks()[FIELD_HEIGHT-1][FIELD_WIDTH-1] != NULL, @"after fill field");
    STAssertTrue(g->getField()->getBlocks()[FIELD_HEIGHT-1][FIELD_WIDTH-1]->getNumber() == g->getLastNumber(), @"after fill field");
    STAssertTrue(g->getFilledBlocks()[FIELD_HEIGHT-1][FIELD_WIDTH-1] == true, @"after fill field");
}

- (void)testSelectDeletable
{
    Game* g = new Game();
    
    // 縦縞
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            g->getField()->getBlocks()[i][j] = new Block(1, j % Block::kColor_Last);
        }
    }
    
    g->selectDeletable(5, 5);
    
    bool** deletableBlocks = g->getDeletableBlocks();
    
    STAssertTrue(deletableBlocks[0][5] == true, @"");
    STAssertTrue(deletableBlocks[3][5] == true, @"");
    STAssertTrue(deletableBlocks[6][5] == true, @"");
    STAssertTrue(deletableBlocks[9][5] == true, @"");
    
    STAssertTrue(deletableBlocks[0][0] == false, @"");
    STAssertTrue(deletableBlocks[4][4] == false, @"");
    STAssertTrue(deletableBlocks[9][9] == false, @"");
}

@end
