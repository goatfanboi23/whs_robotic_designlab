#include <EncodedMotor.h>
#include <DriveTrain.h>
#include <PS2Manager.h>
#include <SimpleMotor.h>

// Generial Motor
#define MOTOR_PULSE 700
#define ENC_MOTOR_MIN_RPM 60
#define ENC_MOTOR_MAX_RPM 255
//MOTOR 1
#define M1_INP1 7
#define M1_INP2 8
#define M1_ENB1 2
#define M1_ENB2 4
#define M1_PWM 6
//MOTOR 2
#define M2_INP1 42
#define M2_INP2 43
#define M2_ENB1 18
#define M2_ENB2 22
#define M2_PWM 44
//MOTOR 3
#define M3_INP1 26
#define M3_INP2 27
#define M3_ENB1 19
#define M3_ENB2 24
#define M3_PWM 45
//MOTOR 4
#define M4_INP1 28
#define M4_INP2 29
#define M4_ENB1 20
#define M4_ENB2 25
#define M4_PWM 46
//spinner
#define SPINNER_INP1 52
#define SPINNER_INP2 53
// PS2 Controller
#define PS2_INP1 12
#define PS2_INP2 10
#define PS2_INP3 9
#define PS2_INP4 11
// LINEAR ACTUTER
#define LA_INT1 48
#define LA_INT2 49

// varables from custom classes
PS2Manager ps2(PS2_INP1,PS2_INP2,PS2_INP3,PS2_INP4);
EncodedMotor motor1(M1_INP1,M1_INP2,M1_ENB1,M1_ENB1,M1_PWM,MOTOR_PULSE);
EncodedMotor motor2(M2_INP1,M2_INP2,M2_ENB1,M2_ENB1,M2_PWM,MOTOR_PULSE);
EncodedMotor motor3(M3_INP1,M3_INP2,M3_ENB1,M3_ENB1,M3_PWM,MOTOR_PULSE);
EncodedMotor motor4(M4_INP1,M4_INP2,M4_ENB1,M4_ENB1,M4_PWM,MOTOR_PULSE);
DriveTrain driveTrain(motor1,motor3,motor2,motor4);
SimpleMotor spinner(SPINNER_INP1,SPINNER_INP2);
SimpleMotor linearActulator(LA_INT1,LA_INT2);

bool tankDrive = true;

// called once at the beinging of the program
void setup() {
  // Every arduio has a diffrent braudRate
  // Mega = 115200, Uno = 9600
  Serial.begin(115200);
  ps2.setup();
  spinner.setup();
  linearActulator.setup();
  driveTrain.setup();
  // format of ps2.addButtonFunction is: hey WHEN this keep is pressed, you should EXECUTE this code
  ps2.addButtonFunction(PSB_RED,[](){
    driveTrain.toggleState();
    spinner.toggleState();
    linearActulator.toggleState();
  });
  ps2.addButtonFunction(PSB_GREEN,[](){
    spinner.toggleMove(); 
  });
  ps2.addButtonFunction(PSB_PINK,[](){
    linearActulator.setMove(true);
    linearActulator.toggleDirection();
  });
  ps2.addButtonFunction(PSB_BLUE,[](){
    if (tankDrive){
      tankDrive = false;
    }else {tankDrive = true;}
  });

  attachInterrupt(digitalPinToInterrupt(M1_ENB1), pulseMotor1, RISING);
  attachInterrupt(digitalPinToInterrupt(M2_ENB1), pulseMotor2, RISING);
  attachInterrupt(digitalPinToInterrupt(M3_ENB1), pulseMotor3, RISING);
  attachInterrupt(digitalPinToInterrupt(M4_ENB1), pulseMotor4, RISING);
}


// Called every frame(after method finishes loop repeates)
void loop() {
  //update values from for ps2 Controller and perform and actions the were tripped by button presses
  ps2.update();
  
  MotorPacket packet;
  Vector lStick = ps2.getCurrentLeftStick();
  Vector rStick = ps2.getCurrentRightStick();
   // I could have made arcadia drive but I am lazy and need sleep
  // if we are in meconoum mode AND the joystick is pushed farther to the left/right then the up/down
  if(!tankDrive && abs(128 - lStick.x) > abs(128-lStick.y)){
    //send a motor packet of side motion (one side has both wheels spinning in OTHER side has both wheels spinning out)
    int spd = analogToSpeed(lStick.x);
    packet = motorPacketOf(spd,spd*-1,spd,spd*-1);
  } else {
    // Normal tank drive where leftStick controls left Motors and right Stick Controls left Motors
    int leftSpeed =  analogToSpeed(lStick.y);
    int rightSpeed =  analogToSpeed(rStick.y);
    packet = motorPacketOf(leftSpeed,rightSpeed,leftSpeed,rightSpeed);
  }
  // Update object after recieving new data
  driveTrain.update(packet);
  spinner.update();
  linearActulator.update();
}

// ==========================================================================================================
//                static functions that are called when encoder sensors are tripped
// ==========================================================================================================
void pulseMotor1(){
  motor1.pulse();
}
void pulseMotor2(){
  motor2.pulse();
}
void pulseMotor3(){
  motor3.pulse();
}
void pulseMotor4(){
  motor4.pulse();
}

// ==========================================================================================================
//              Utility Functions (Should I put them in a corrisponding class? Yes. do I care? No.)
// ==========================================================================================================
//MotorPacket motorPacketOf(int spd1,int spd2,int spd3,int spd4){
//  MotorPacket packet;
//  packet.motor1Speed = spd1;
//  packet.motor2Speed = spd2;
//  packet.motor3Speed = spd3;
//  packet.motor4Speed = spd4;
//  return packet;
//}

// takes and analog input(0-255) and maps to a value between the encodedMotor min and max rpm(60-200)
int analogToSpeed(int value){
  int vel = abs(value-128);
  int fin = vel == 0 ? 0 : map(vel,0,255,ENC_MOTOR_MIN_RPM,ENC_MOTOR_MAX_RPM);
  fin *= value < 128 ? 1 : -1;
  return fin;
}
