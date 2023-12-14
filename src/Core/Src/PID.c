#include"PID.h"

void initPID(PIDer* this, float P, float I, float D){
    this->P = P;
    this->I = I;
    this->D = D;
    this->LastError = 0.0;
    this->PrevError = 0.0;
    this->SumError = 0.0;
    this->Output = 0.0;
}