#include "Arduino.h"
#include "EncodedMotor.h"
EncodedMotor::EncodedMotor(uint16_t inp1,uint16_t inp2, uint16_t encA, uint16_t encB,uint16_t pwm,unsigned int pulseRev) {
    this->motorControllerInput1 = inp1;
    this->motorControllerInput2 = inp2;
    this->encoderA = encA;
    this->encoderB = encB;
    this->pwmPin = pwm;
    this->pulseCount = 0;
    this->pulsesPerRevolution = pulseRev;
}
void EncodedMotor::setup(){
    pinMode(this->encoderA,INPUT_PULLUP);
    pinMode(this->encoderB , INPUT);
    pinMode(this->motorControllerInput1,OUTPUT);
    pinMode(this->motorControllerInput2,OUTPUT);
    pinMode(this->pwmPin,OUTPUT);
}
void EncodedMotor::pulse(){
    int val = digitalRead(this->encoderB);
    this->dir = (val == HIGH);
    this->pulseCount += this->dir ? 1 : -1;
}
void EncodedMotor::stop(){
    digitalWrite(this->motorControllerInput1,LOW);
    digitalWrite(this->motorControllerInput2,LOW);
    this->speed = 0;
}
void EncodedMotor::toggleState(){
    this->enabled = !this->enabled;
    stop();
}

void EncodedMotor::update() {
    // Record the time
    if (!this->enabled){return;}
    
    analogWrite(this->pwmPin,abs(this->speed));
    this->currentMillis = millis();
    // If one second has passed, update the number of pulses
    if (this->currentMillis - this->previousMillis > EncodedMotor::interval) {
        this->previousMillis = this->currentMillis;
        // Calculate revolutions per minute
        this->rpm = (float)(this->pulseCount * 60 / this->pulsesPerRevolution);
        this->anglVel = (this->rpm) * (EncodedMotor::rpm_to_radians);   
        this->anglVelDeg = (this->anglVel)  *  (EncodedMotor::rad_to_deg);
        this->pulseCount = 0;
    }
}
void EncodedMotor::move(){
    if (!this->enabled){return;}
    if(this->speed > 0){ 
        digitalWrite(this->motorControllerInput1,HIGH);
        digitalWrite(this->motorControllerInput2,LOW);
    }else {
        digitalWrite(this->motorControllerInput2,HIGH);
        digitalWrite(this->motorControllerInput1,LOW);
    }
}

void EncodedMotor::setSpeed(int spd){
    this->speed = spd;
}
int EncodedMotor::getSpeed() const {
    return this->speed;
}
float EncodedMotor::getRPM() const {
    return (float)(this->pulseCount * 60 / this->pulsesPerRevolution);
}
bool EncodedMotor::getDirection() const {
    return this->dir;
}             
uint16_t EncodedMotor::getEncoderA() const {
    return this->encoderA;
}
