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

@end
