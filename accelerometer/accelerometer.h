#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "board.h"

void accel_init();
void accel_initSPI();
void accel_spiSetSpeed(unsigned char speed);
unsigned char accel_spiSend(unsigned char outgoing, int last);
void accel_setup();
unsigned char accel_readControlRegister();
unsigned int accel_readAxis(unsigned char axis);
float accel_rawToG(unsigned int rawValue, unsigned int zeroValue);
float accel_readAxisG(unsigned char axis, unsigned int zeroValue);
                      

#endif /*ACCELEROMETER_H_*/