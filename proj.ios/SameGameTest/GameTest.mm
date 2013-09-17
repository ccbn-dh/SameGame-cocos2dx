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

- (void)testDelete
{
    Game* g = new Game();
    
    // 縦縞
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            g->getField()->getBlocks()[x][y] = new Block(1, y % Block::kColor_Last);
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
    
    g->deleteDeletable();
    
    STAssertTrue(g->getField()->getBlocks()[0][5] == NULL, @"deleted");
    STAssertTrue(g->getField()->getBlocks()[3][5] == NULL, @"deleted");
    STAssertTrue(g->getField()->getBlocks()[6][5] == NULL, @"deleted");
    STAssertTrue(g->getField()->getBlocks()[9][5] == NULL, @"deleted");
    
    STAssertTrue(g->getField()->getBlocks()[0][0] != NULL, @"not deleted");
    STAssertTrue(g->getField()->getBlocks()[4][4] != NULL, @"not deleted");
    STAssertTrue(g->getField()->getBlocks()[9][9] != NULL, @"not deleted");
    
    g->dropBlocks();
    
    STAssertTrue(g->getField()->getBlocks()[0][5] != NULL, @"droped");
    STAssertTrue(g->getField()->getBlocks()[0][9] == NULL, @"droped");
}

@end
