//
//  Position.h
//  hoop
//
//  Created by Willem Ave on 5/7/16.
//  Copyright © 2016 Willem Ave. All rights reserved.
//

#ifndef Position_h
#define Position_h

#include <math.h>

struct Position {
    float ax, ay, az, gx, gy, gz, mx, my, mz; // variables to hold latest sensor data values
    float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
    float pitch, yaw, roll, heading;
  float raw;
};

#endif /* Position_h */
