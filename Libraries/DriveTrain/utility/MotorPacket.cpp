#include "MotorPacket.h"
#include "Arduino.h"
MotorPacket::MotorPacket() {
    this->motor1Speed = 0;
    this->motor2Speed = 0;
    this->motor3Speed = 0;
    this->motor4Speed = 0;
}
MotorPacket::MotorPacket(int spd1, int spd2, int spd3, int spd4) {
    this->motor1Speed = spd1;
    this->motor2Speed = spd2;
    this->motor3Speed = spd3;
    this->motor4Speed = spd4;
}

int MotorPacket::getSpd1() const {
    return this->motor1Speed;
}
int MotorPacket::getSpd2() const {
    return this->motor2Speed;
}
int MotorPacket::getSpd3() const {
    return this->motor3Speed;
}
int MotorPacket::getSpd4() const {
    return this->motor4Speed;
}
