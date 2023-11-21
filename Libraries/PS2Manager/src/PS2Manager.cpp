#include "Arduino.h"
#include "PS2Manager.h"
#include <util/atomic.h>
#include <PS2X_lib.h>
#include <VectorUtils.h>

struct ButtonMap {
    uint16_t button;
    buttonFunction function;
}

PS2Manager::PS2Manager(uint16_t pin1,uint16_t pin2, uint16_t pin3, uint16_t pin4) {
    this->ps2Inp1 = pin1;
    this->ps2Inp2 = pin2;
    this->ps2Inp3 = pin3;
    this->ps2Inp4 = pin4;
}
void PS2Manager::setup(){
    this->ps2x.config_gamepad(this->ps2Inp1,this->ps2Inp2,this->ps2Inp3,this->ps2Inp4,true,true);
}
void PS2Manager::update(){
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
        ps2x.read_gamepad(false,0);
    }
    updateStickValues();
    updateButtonState();

}
void PS2Manager::addButtonFunction(uint16_t button, buttonFunction function){
    int index = getButtonIndex(button);
    if (index != -1){
      this->bm[index].function = function;
    }else{
        this->lastButtonIndex++;
        this->bm[this->lastButtonIndex].button = button;
        this->bm[this->lastButtonIndex].function = function;
    }
}
bool PS2Manager::setFuncAtButtonIndex(int index,buttonFunction function){
    if(index > this->lastButtonIndex){
        return false;
    }
    this->bm[index].function = function;
    return true;
}

int PS2Manager::getButtonIndex(uint16_t button){
    for (int i = 0; i <= this->lastButtonIndex; i++){
        if (this->bm[i].button == button){
            return i;
        }
    }
    return -1;
}
void PS2Manager::updateStickValues(){
    this->pastLeftStick = this->currentLeftStick;
    this->pastRightStick = this->currentRightStick;
    this->currentRightStick.x = this->ps2x.Analog(PSS_RX);
    this->currentRightStick.y = this->ps2x.Analog(PSS_RY);
    this->currentLeftStick.x = this->ps2x.Analog(PSS_LX);
    this->currentLeftStick.y = this->ps2x.Analog(PSS_LY);
}
void PS2Manager::updateButtonState(){
  if (this->ps2x.NewButtonState()){ 
    for(int i = 0; i <= this->lastButtonIndex; i++){
      if(ps2x.ButtonPressed(this->bm[i].button)){
        this->bm[i].function();
      }
    }
  }
}

Vector PS2Manager::getCurrentLeftStick() const{
    Vector vect;
    vect.x = this->currentLeftStick.x;
    vect.y = this->currentLeftStick.y;
    return vect;
}

Vector PS2Manager::getCurrentRightStick() const{
    Vector vect;
    vect.x = this->currentRightStick.x;
    vect.y = this->currentRightStick.y;
    return vect;
}

Vector PS2Manager::getPastLeftStick() const{
    Vector vect;
    vect.x = this->pastLeftStick.x;
    vect.y = this->pastLeftStick.y;
    return vect;
}

Vector PS2Manager::getPastRightStick() const{
    Vector vect;
    vect.x = this->pastRightStick.x;
    vect.y = this->pastRightStick.y;
    return vect;
}

PS2X PS2Manager::getPS2X() const{
    return this->ps2x;
}