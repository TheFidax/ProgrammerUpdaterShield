#include "Arduino.h"

#define ISP_LED 6
#define I2C_LED 5

#define I2C_PULLUP 3

typedef enum { ISP, I2C } Mode;
Mode mode;

void setup() {
  pinMode(ISP_LED, OUTPUT);
  pinMode(I2C_LED, OUTPUT);

  if(digitalRead(I2C_PULLUP) == HIGH) {
    mode = I2C;
  }
  else {
    mode = ISP;
  }
  
  if (mode == ISP) {
    digitalWrite(ISP_LED, HIGH);
    setup_ArduinoISP();
    while(1) {
      loop_ArduinoISP();
    }
  }
  else if (mode == I2C) {
    digitalWrite(I2C_LED, HIGH);
    setup_ArduinoI2C();
    while(1) {
      loop_ArduinoI2C();
    }
  }
}

void loop() {}
