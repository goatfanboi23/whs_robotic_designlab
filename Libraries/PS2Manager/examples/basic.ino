#include <PS2Manager.h>

// PS2 Controller
#define PS2_INP1 12
#define PS2_INP2 10
#define PS2_INP3 9
#define PS2_INP4 11

// called once at the start of the program
void setup() {
    Serial.begin(9600);
    ps2.setup();
    // format of ps2.addButtonFunction is: hey WHEN this keep is pressed, you should EXECUTE this code
    ps2.addButtonFunction(PSB_RED,[](){
        Serial.println("RED!");
    });
    ps2.addButtonFunction(PSB_GREEN,[](){
        Serial.println("GREEN!");
    });
    ps2.addButtonFunction(PSB_PINK,[](){
        Serial.println("PINK!");
    });
    ps2.addButtonFunction(PSB_BLUE,[](){
        Serial.println("BLUE!");
    });
}


// Called every frame(after method finishes loop repeats)
void loop() {
    //update values from for ps2 Controller and perform and actions that were tripped by button presses
    ps2.update();
    //if you have buttons presses firing twice uncomment following line
    //delay(10);
}
