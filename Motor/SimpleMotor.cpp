#include "Arduino.h"
#include "SimpleMotor.h"
SimpleMotor::SimpleMotor(uint16_t inp1,uint16_t inp2) {
    this->motorControllerInput1 = inp1;
    this->motorControllerInput2 = inp2;
}
void SimpleMotor::setup(){
    pinMode(this->motorControllerInput1,OUTPUT);
    pinMode(this->motorControllerInput2,OUTPUT);
}

void SimpleMotor::stop(){
    digitalWrite(this->motorControllerInput1,LOW);
    digitalWrite(this->motorControllerInput2,LOW);
    moving = false;
}
void SimpleMotor::toggleState(){
    this->enabled = !this->enabled;
}
void SimpleMotor::toggleDirection(){
    this->dir = !this->dir;
}

void SimpleMotor::update() {
    if(this->enabled && this->moving == true){
        if(dir){
            digitalWrite(this->motorControllerInput1,HIGH);
            digitalWrite(this->motorControllerInput2,LOW);
        }else{
            digitalWrite(this->motorControllerInput1,LOW);
            digitalWrite(this->motorControllerInput2,HIGH);
        }
    } else {
        stop();
    }
}
void SimpleMotor::toggleMove(){
    this->moving = !this->moving;
}
void SimpleMotor::setDirection(bool b){
    this->dir = b;
}
void SimpleMotor::setMove(bool b){
    this->moving = b;
}
void SimpleMotor::setState(bool b){
    this->enabled = b;
}