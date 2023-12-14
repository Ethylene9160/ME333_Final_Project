#include"PID.h"


void smoothControl(PIDer* this, float targetV){
    float error = targetV - this->Output;
    this->SumError += error;
    this->Output = this->Proportion * error + this->Integral * this->SumError + this->Derivative * (error - this->LastError);
    this->LastError = error;
    //TODO: smooth control the v.

}