#include"MyMotor.h"
void initMotor(MyMotor* this, int MotorID, PIDer* pider){
    this->MotorID = MotorID;
    this->vx = 0.0;
    this->vy = 0.0;
    this->pider = pider;
}

void smoothControl(MyMotor* this, float targetV){
    float error = targetV - this->pider->Output;
    this->pider->SumError += error;
    this->pider->Output = this->pider->P * error + this->pider->I * this->pider->SumError + this->pider->D * (error - this->pider->LastError);
    this->pider->LastError = error;
    //
}
