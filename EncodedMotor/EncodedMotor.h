#ifndef EncodedMotor_h
#define EncodedMotor_h
#include "Arduino.h"
class EncodedMotor {
public:
    static constexpr float rpm_to_radians = 0.10471975512;
    static constexpr float rad_to_deg = 57.29578;
    static constexpr int interval = 1000;
    EncodedMotor(uint16_t inp1,uint16_t inp2, uint16_t encA, uint16_t encB,uint16_t pwm,unsigned int pulseRev);
    void setup();
    void pulse();
    void update();
    void move();
    void stop();
    void setSpeed(int speed);
    int getSpeed() const;
    float getRPM() const;
    bool getDirection() const;
    void setTargetDir(bool tarDir);
    uint16_t getEncoderA() const;
    void toggleState();

private:
    long previousMillis = 0;
    long currentMillis = 0;
    // True = Forward; False = Reverse
    bool dir = true;

    // Variable for angular velocity measurement
    float anglVel = 0;
    float anglVelDeg = 0;
    volatile long pulseCount = 0;
    uint16_t motorControllerInput1;
    uint16_t motorControllerInput2;
    uint16_t encoderA;
    uint16_t encoderB;
    uint16_t pwmPin;
    int speed = 0; 
    float rpm = 0;
    unsigned int pulsesPerRevolution;
    bool enabled = false;
};

#endif