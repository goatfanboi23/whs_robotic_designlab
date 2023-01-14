#ifndef DriveTrain_h
#define DriveTrain_h
#include "Arduino.h"
#include "EncodedMotor.h"
typedef struct {
  int motor1Speed;
  int motor2Speed;
  int motor3Speed;
  int motor4Speed;
} MotorPacket;
class DriveTrain {
public:
    DriveTrain(EncodedMotor m1,EncodedMotor m2,EncodedMotor m3,EncodedMotor m4);
    void setup();
    void toggleState();
    void update(MotorPacket packet);
    void stop();
private:
    EncodedMotor motor1;
    EncodedMotor motor2;
    EncodedMotor motor3;
    EncodedMotor motor4;
    void updateMotors();
   
};

#endif