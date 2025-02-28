#ifndef TB6612_h
#define TB6612_h

#define DEFAULTSPEED 255

class Motor{
    public:
        Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin); 

        void drive(int speed);
        void drive(int speed, int duration);

        void brake();
        void standby();

    private:
        int In1, In2, PWM, Offset, Standby;

        void fwd(int speed);
        void rev(int speed);
};

void forward(Motor motor1, Motor motor2, int speed);
void forward(Motor motor1, Motor motor2);

void left(Motor left, Motor right, int speed);
void right(Motor left, Motor right, int speed);

void back(Motor left, Motor right, int speed);
void back(Motor left, Motor right);

void brake(Motor motor1, Motor motor2);

#endif
