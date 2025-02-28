from gpiozero import *
from time import sleep

def initDriver(STBYpin):
    Standby = OutputDevice(STBYpin)
    return Standby

class Motor:
    def __init__(self, In1pin, In2pin, PWMpin, offset, Standby):
        self.In1 = OutputDevice(In1pin)
        self.In2 = OutputDevice(In2pin)
        self.PWM = PWMOutputDevice(PWMpin)
        self.Offset = offset
        self.Standby = Standby
    
    def __fwd(self, speed):
        self.In1.on()
        self.In2.off()
        self.PWM.value = speed
    
    def __rev(self, speed):
        self.In1.off()
        self.In2.on()
        self.PWM.value = speed
    
    def drive(self, speed, duration=0):
        self.Standby.on()
        speed = speed * self.Offset
        if(speed >= 0):
            self.__fwd(speed)
        else:
            self.__rev(-speed)
        sleep(duration)

    def brake(self):
        self.In1.on()
        self.In2.on()
        self.PWM.value = 0

    def standby(self):
        self.Standby.off()
    
def forward(motor1: Motor, motor2: Motor, speed=1):
    motor1.drive(speed)
    motor2.drive(speed)
def back(motor1: Motor, motor2: Motor, speed=1):
    tmp = abs(speed)
    motor1.drive(-tmp)
    motor2.drive(-tmp)

def left(left: Motor, right: Motor, speed=1):
    tmp = abs(speed)/2
    left.drive(tmp)
    right.drive(-tmp)
def right(left: Motor, right: Motor, speed=1):
    tmp = abs(speed)/2
    left.drive(-tmp)
    right.drive(tmp)

def brake(motor1: Motor, motor2: Motor):
    motor1.brake()
    motor2.brake()
