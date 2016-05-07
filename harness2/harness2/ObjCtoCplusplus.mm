//
//  ObjCtoCplusplus.m
//  harness2
//
//  Created by Willem Ave on 4/7/16.
//  Copyright © 2016 Willem Ave. All rights reserved.
//

#import "ObjcObject.h"
#import "Renderer.h"

@interface ObjcObject () {
  Renderer* wrapped; // Pointer! Will be initialised to NULL by alloc.
}
@end

@implementation ObjcObject
- (id)initWithSize:(int)size
{
  self = [super init];
  if (self)
  {
    wrapped = new Renderer(size);
    if (!wrapped) self = nil;
  }
  return self;
}

- (void)render:(NSArray*)array_out
{
  int count = [array_out count];
  float *array = new float[count];
  self.wrapped.render(array_out, length)
}