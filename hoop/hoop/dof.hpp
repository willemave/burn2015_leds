//
//  dof.hpp
//  hoop
//
//  Created by Willem Ave on 1/25/16.
//  Copyright © 2016 Willem Ave. All rights reserved.
//

#ifndef dof_hpp
#define dof_hpp

#include <SPI.h>
#include <i2c_t3.h>  // Teensy 3.1-specific  Wire1.h library
#include <SFE_LSM9DS0.h>

void setupdof();
void loopy();
void MS5637Reset();
void MS5637PromRead(uint16_t * destination);
unsigned char MS5637checkCRC(uint16_t * n_prom);
uint32_t MS5637Read(uint8_t CMD, uint8_t OSR);
unsigned char MS5637checkCRC(uint16_t * n_prom);
void printHeading(float hx, float hy);
void printOrientation(float x, float y, float z);
void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);

#endif /* dof_hpp */
