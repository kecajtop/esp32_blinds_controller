#include "Arduino.h"
#include "Wire.h"
#include "variables.h"

extern int countOfI2cDevices;
extern int countOfI2cDevices;

void i2c_init(int *_result)
 {
  *_result = Wire.begin(SDApin,  SCLpin);

  Wire.setClock(I2C_CLKRATE);  
 }

 