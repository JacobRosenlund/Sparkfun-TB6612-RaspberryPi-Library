# Sparkfun-TB6612 RaspberryPi Library
This Library is for the [Sparkfun TB6612FNG Motor Driver](https://www.sparkfun.com/sparkfun-motor-driver-dual-tb6612fng-1a.html) and has been re-written for the RPi (it isbased on [this](https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library) Arduino Library by [Sparkfun](https://github.com/sparkfun)).

**Changes to Original**
- Replaced `Arduino.h` with `wiringPi.h`
- Replaced `analogWrite()` with RPi PWM utilities

## How to Use
To use this library, you need to place both `TB6612.h` and `TB6612.cpp` in your project's folder, then include `wiringPi.h` and `"TB6612.h"`:
```cpp
// This example code wiggles the two motors

#include <wiringPi.h>
#include "TB6612.h"

#define PWMA 11
#define AIN2 0
#define AIN1 5
#define STBY 6
#define BIN1 13
#define BIN2 19
#define PWMB 26

#define OFFSET_A 1
#define OFFSET_B 1

Motor motor1 = Motor(AIN1, AIN2, PWMA, OFFSET_A, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, OFFSET_B, STBY);

void setup(){
  // `wiringPiSetupGpio();` has been called in TB6612.cpp, so calling it again is not needed

  // Set all pins high to force `brake()` (Just to be safe)
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
  digitalWrite(STBY, HIGH);
  delay(800); // Just to make sure everything is all set up first
}

int main(void){
  setup();

  right(motor1, motor2, 150); // You might have to change motor order
  delay(100);
  left(motor1, motor2, 150);
  delay(100);
  brake(motor1, motor2);
}
```

To compile:
```
g++ TB6612.cpp myapp.cpp -o myapp -l wiringPi
```

## Issues
Please submit an issue if you find any issues!
