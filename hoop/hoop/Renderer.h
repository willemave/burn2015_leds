//
//  Renderer.h
//  hoop
//
//  Created by Willem Ave on 4/7/16.
//  Copyright © 2016 Willem Ave. All rights reserved.
//

#ifndef Renderer_h
#define Renderer_h

class Renderer
{
  unsigned int leds;
public:
  Renderer(int leds): leds(leds) {}
  Renderer(): leds(100) {}
  
  void consumeEvents();
  
  void render(int out[], int length);
};

#endif /* Renderer_h */
