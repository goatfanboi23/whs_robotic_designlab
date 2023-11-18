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

EncodedMotor motor1(M1_INP1,M1_INP2,M1_ENB1,M1_ENB1,M1_PWM,MOTOR_PULSE);
EncodedMotor motor2(M2_INP1,M2_INP2,M2_ENB1,M2_ENB1,M2_PWM,MOTOR_PULSE);
EncodedMotor motor3(M3_INP1,M3_INP2,M3_ENB1,M3_ENB1,M3_PWM,MOTOR_PULSE);
EncodedMotor motor4(M4_INP1,M4_INP2,M4_ENB1,M4_ENB1,M4_PWM,MOTOR_PULSE);
DriveTrain driveTrain(motor1,motor3,motor2,motor4);

bool tankDrive = true;

// called once at the beinging of the program
void setup() {
    // Every arduio has a diffrent braudRate
    // Mega = 115200, Uno = 9600
    Serial.begin(9600);
    driveTrain.setup();

    attachInterrupt(digitalPinToInterrupt(M1_ENB1), pulseMotor1, RISING);
    attachInterrupt(digitalPinToInterrupt(M2_ENB1), pulseMotor2, RISING);
    attachInterrupt(digitalPinToInterrupt(M3_ENB1), pulseMotor3, RISING);
    attachInterrupt(digitalPinToInterrupt(M4_ENB1), pulseMotor4, RISING);
}


// Called every frame(after method finishes loop repeates)
void loop() {
    MotorPacket packet = MotorPacket(150,150,150,150);
    driveTrain.update(packet);
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

// takes and analog input(0-255) and maps to a value between the encodedMotor min and max rpm(60-200)
int analogToSpeed(int value){
    int vel = abs(value-128);
    int fin = vel == 0 ? 0 : map(vel,0,255,ENC_MOTOR_MIN_RPM,ENC_MOTOR_MAX_RPM);
    fin *= value < 128 ? 1 : -1;
    return fin;
}
