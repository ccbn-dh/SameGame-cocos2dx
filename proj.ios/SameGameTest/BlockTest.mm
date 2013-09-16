#import "BlockTest.h"
#import "Block.h"

@implementation BlockTest

- (void)testBlock
{
    Block* b = new Block(100, Block::kColor_White);
    
    STAssertTrue(b->getNumber() == 100, @"");
    STAssertTrue(b->getColor() == Block::kColor_White, @"");
}

@end
