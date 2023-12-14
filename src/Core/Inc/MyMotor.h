#include"MyMotor.h"
#include"PID.h"
#ifndef MY_MOTOR
#define MY_MOTOR 1

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
