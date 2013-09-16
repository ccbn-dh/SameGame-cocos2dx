#import "FieldTest.h"
#import "Field.h"

@implementation FieldTest

- (void)testField
{
    Field* f = new Field();
    Block*** b = f->getBlocks();
    
    STAssertTrue(b != NULL, @"");
    
    delete f;
}

@end
