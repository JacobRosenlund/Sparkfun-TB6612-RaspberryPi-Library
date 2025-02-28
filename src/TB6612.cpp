#include "TB6612.h"
#include <cmath>
#include <wiringPi.h>
#include <softPwm.h>

Motor::Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin){
    wiringPiSetupGpio();

    In1 = In1pin;
    In2 = In2pin;
    PWM = PWMpin;
    Standby = STBYpin;
    Offset = offset;

    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(PWM, OUTPUT);
    softPwmCreate(PWM, 1, 255);
    pinMode(Standby, OUTPUT);
}

void Motor::drive(int speed){
    digitalWrite(Standby, HIGH);
    speed = speed * Offset;
    if(speed >= 0){
        fwd(speed);
    } else{
        rev(-speed);
    }
}

void Motor::drive(int speed, int duration){
    drive(speed);
    delay(duration);
}

void Motor::fwd(int speed){
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    softPwmWrite(PWM, speed);
}

void Motor::rev(int speed){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    softPwmWrite(PWM, speed);
}

void Motor::brake(){
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    softPwmWrite(PWM, 0);
}

void Motor::standby(){
    digitalWrite(Standby, LOW);
}

void forward(Motor motor1, Motor motor2, int speed){
    motor1.drive(speed);
    motor2.drive(speed);
}
void forward(Motor motor1, Motor motor2){
    motor1.drive(DEFAULTSPEED);
    motor2.drive(DEFAULTSPEED);
}

void back(Motor motor1, Motor motor2, int speed)
{
	int temp = abs(speed);
	motor1.drive(-temp);
	motor2.drive(-temp);
}
void back(Motor motor1, Motor motor2)
{
	motor1.drive(-DEFAULTSPEED);
	motor2.drive(-DEFAULTSPEED);
}

void left(Motor left, Motor right, int speed)
{
	int temp = abs(speed)/2;
	left.drive(-temp);
	right.drive(temp);
	
}
void right(Motor left, Motor right, int speed)
{
	int temp = abs(speed)/2;
	left.drive(temp);
	right.drive(-temp);
	
}

void brake(Motor motor1, Motor motor2)
{
	motor1.brake();
	motor2.brake();
}
