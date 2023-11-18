#ifndef MotorPacket_h
#define MotorPacket_h
#include "Arduino.h"
class MotorPacket {
public:
    MotorPacket(int spd1, int spd2, int spd3, int spd4);
    MotorPacket();
    int getSpd1() const;
    int getSpd2() const;
    int getSpd3() const;
    int getSpd4() const;

private:
    int motor1Speed;
    int motor2Speed;
    int motor3Speed;
    int motor4Speed;

};

#endif

