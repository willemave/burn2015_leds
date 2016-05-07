//
//  Renderer.cpp
//  hoop
//
//  Created by Willem Ave on 4/7/16.
//  Copyright © 2016 Willem Ave. All rights reserved.
//

#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

struct HSV {
  int H;
  int S;
  int V;
};

Renderer::render(int out[], int length)
{
  for (int i; i < length; ++int) {
    out[i] = HSV(rand % 100 + 1,rand % 100 + 1,rand % 100 + 1);
  }
}