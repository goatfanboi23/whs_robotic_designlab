#ifndef SimpleMotor_h
#define SimpleMotor_h
#include "Arduino.h"
class SimpleMotor {
public:
    SimpleMotor(uint16_t inp1,uint16_t inp2);
    void setup();
    void update();
    void stop();
    void toggleState();
    void toggleDirection();
    void toggleMove();
    void setMove(bool b);
    void setState(bool b);
    void setDirection(bool b);

private:
    uint16_t motorControllerInput1;
    uint16_t motorControllerInput2;
    bool enabled = false;
    bool moving = false;
    bool dir = false;
};

#endif