#include <EncodedMotor.h>
#include <DriveTrain.h>
#include <PS2Manager.h>
#include <SimpleMotor.h>

#define MOTOR_PULSE 700

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

// FOR LINEAR ACTUTER
#define LA_INT1 48
#define LA_INT2 49


PS2Manager ps2(PS2_INP1,PS2_INP2,PS2_INP3,PS2_INP4);
EncodedMotor motor1(M1_INP1,M1_INP2,M1_ENB1,M1_ENB1,M1_PWM,MOTOR_PULSE);
EncodedMotor motor2(M2_INP1,M2_INP2,M2_ENB1,M2_ENB1,M2_PWM,MOTOR_PULSE);
EncodedMotor motor3(M3_INP1,M3_INP2,M3_ENB1,M3_ENB1,M3_PWM,MOTOR_PULSE);
EncodedMotor motor4(M4_INP1,M4_INP2,M4_ENB1,M4_ENB1,M4_PWM,MOTOR_PULSE);
DriveTrain driveTrain(motor1,motor3,motor2,motor4);
SimpleMotor spinner(SPINNER_INP1,SPINNER_INP2);
SimpleMotor linearActulator(LA_INT1,LA_INT2);
bool tankDrive = true;

void setup() {
  Serial.begin(9600);
  ps2.setup();
  spinner.setup();
  linearActulator.setup();
  driveTrain.setup();
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

void loop() {
  ps2.update();
  MotorPacket packet;
  Vector lStick = ps2.getCurrentLeftStick();
  Vector rStick = ps2.getCurrentRightStick();

  if(!tankDrive && abs(128-lStick.x) > abs(128-lStick.y)){
    int spd = analogToSpeed(lStick.x);
    packet.motor1Speed = spd;
    packet.motor2Speed = spd * -1;
    packet.motor3Speed = spd * -1;
    packet.motor4Speed = spd;
  } else {
    int leftSpeed =  analogToSpeed(lStick.y);
    int rightSpeed =  analogToSpeed(rStick.y);

    packet.motor1Speed = leftSpeed;
    packet.motor2Speed = rightSpeed;
    packet.motor3Speed = leftSpeed;
    packet.motor4Speed = rightSpeed;
  }
  
  driveTrain.update(packet);
  spinner.update();
  linearActulator.update();
}

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

int analogToSpeed(int value){
  int vel = abs(value-128);
  int fin = vel == 0 ? 0 : map(vel,0,255,60,255);
  fin *= value < 128 ? 1 : -1;
  return fin;
}
