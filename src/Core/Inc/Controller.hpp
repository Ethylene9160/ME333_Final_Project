#ifndef MY_CONTROLLER
#define MY_CONTROLLER 1
#include<stdlib.h>
#include<stdio.h>

#ifndef MY_CONTROLLER

#ifdef __cplusplus
extern "C" {
#endif

class Controller{
private:
    int motorID;
    float p;
    float i;
    float d;

    float lastError;
    float error;
    float integral;
    float derivative;
    float targetVelocity;
    float currentVelocity;
public:
    Controller();

    Controller(int motorID);

    Controller(int motorID, float p, float i, float d);

    void setTargetVelocity(float targetVelocity);

    float getCurrentVelocity();


};


#ifdef __cplusplus
}
#endif
#endif
#endif // DEBUG