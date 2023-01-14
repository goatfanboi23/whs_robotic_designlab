#include "Arduino.h"
#include "DriveTrain.h"
#include "EncodedMotor.h"
DriveTrain::DriveTrain(EncodedMotor m1,EncodedMotor m2,EncodedMotor m3,EncodedMotor m4): motor1(m1), motor2(m2), motor3(m3),motor4(m4){};
void DriveTrain::setup(){
    this->motor1.setup();
    this->motor2.setup();
    this->motor3.setup();
    this->motor4.setup();
    this->stop();
}
void DriveTrain::update(MotorPacket packet){
    this->motor1.setSpeed(packet.motor1Speed);
    this->motor2.setSpeed(packet.motor2Speed);   
    this->motor3.setSpeed(packet.motor3Speed);
    this->motor4.setSpeed(packet.motor4Speed);    

    if(packet.motor1Speed == 0 && packet.motor2Speed == 0 &&packet.motor3Speed == 0 && packet.motor4Speed == 0){
        stop();
    } else {
        this->motor1.move();
        this->motor2.move();
        this->motor3.move();
        this->motor4.move();
    }
    
    updateMotors();
}
void DriveTrain::stop(){
    this->motor1.stop();
    this->motor2.stop();
    this->motor3.stop();
    this->motor4.stop();
}
void DriveTrain::toggleState(){
    this->motor1.toggleState();
    this->motor2.toggleState();
    this->motor3.toggleState();
    this->motor4.toggleState();
}

void DriveTrain::updateMotors(){
    this->motor1.update();
    this->motor2.update();
    this->motor3.update();
    this->motor4.update();
}

