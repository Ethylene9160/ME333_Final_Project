
#ifndef MY_MOTOR
#define MY_MOTOR 1
#include "usart.h"
#include"PID.h"
//define the id of the 4 motors
#define LEFT_FORWARD 2
#define RIGHT_FORWARD 1
#define LEFT_BACKWARD 3
#define RIGHT_BACKWARD 4
#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    int MotorID;                        //MotorID
    float vx;
    float vy;
    PIDer* pider;                       //pider
}MyMotor;

void initMotor(MyMotor* this, int MotorID, PIDer* pider);

void smoothControl(MyMotor* this, float targetV);

#ifdef __cplusplus
}
#endif

#endif
