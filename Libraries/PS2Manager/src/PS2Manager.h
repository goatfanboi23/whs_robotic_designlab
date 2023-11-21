#ifndef PS2Manager_h
#define PS2Manager_h
#include "Arduino.h"
#include <PS2X_lib.h>
#include <util/atomic.h>
#include <VectorUtils.h>

// empty function used for lamdas
typedef void (*buttonFunction)();

// key value pair for buttons and desired function

typedef struct {
    uint16_t button;
    buttonFunction function;
} ButtonMap;

class PS2Manager {
public:
    PS2Manager(uint16_t pin1, uint16_t pin2, uint16_t pin3, uint16_t pin4);
    void setup();
    void update();
    bool setFuncAtButtonIndex(int index, buttonFunction function);
    int getButtonIndex(uint16_t button);
    void addButtonFunction(uint16_t button, buttonFunction function);
    void updateStickValues();
    void updateButtonState();
    Vector getCurrentLeftStick() const;
    Vector getCurrentRightStick() const;
    Vector getPastLeftStick() const;
    Vector getPastRightStick() const;
    PS2X getPS2X() const;

private:
    ButtonMap bm[32];
    //previus vector of the left analog stick
    Vector currentLeftStick;
    Vector currentRightStick;
    Vector pastLeftStick;
    Vector pastRightStick;
    int lastButtonIndex = -1;
    uint16_t ps2Inp1;
    uint16_t ps2Inp2;
    uint16_t ps2Inp3;
    uint16_t ps2Inp4;
    // PS2x object for reffernecing controller functions and buttons
    PS2X ps2x; 
};

#endif