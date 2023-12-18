#include"MyMotor.h"
void initMotor(MyMotor* this, int MotorID, PIDer* pider){
    this->MotorID = MotorID;
    this->targetV = 0.0;
    this->pider = pider;
}

void initAllMotors(){
    //todo: adjust pid
    initPID(&leftforwardPider, 1.2, 0.35, 0.0);
    initPID(&leftbackwardPider, 1.2, 0.35, 0.0);
    initPID(&rightforwardPider, 1.2, 0.35, 0.0);
    initPID(&rightbackwardPider, 1.2, 0.35, 0.0);

    initMotor(&leftforwardMotor, LEFT_FORWARD, &leftforwardPider);
    initMotor(&leftbackwardMotor, LEFT_BACKWARD, &leftbackwardPider);
    initMotor(&rightforwardMotor, RIGHT_FORWARD, &rightforwardPider);
    initMotor(&rightbackwardMotor, RIGHT_BACKWARD, &rightbackwardPider);
}

void smoothControl(MyMotor* this, float targetV){
    float error = targetV - this->pider->currentV;
    this->pider->SumError += error;
    this->pider->currentV = this->pider->P * error + this->pider->I * this->pider->SumError + this->pider->D * (error - this->pider->LastError);
    this->pider->LastError = error;
    //
}

void piControl(MyMotor* this){
    //this->pider->currentV = this->targetV;
    static float step = 0.1;
    if(this->targetV > this->pider->currentV){
        this->pider->currentV += step;
    }else if(this->targetV < this->pider->currentV){
        this->pider->currentV -= step;
    }
    this->pider->currentV = this->targetV;
    return; 
    float error = this->targetV - this->pider->currentV;
    this->pider->SumError += error;
    this->pider->currentV = this->pider->P * error + this->pider->I * this->pider->SumError;
    if(this->pider->currentV > MAX_SPEED){
        this->pider->currentV = MAX_SPEED;
    }
    else if(this->pider->currentV < -MAX_SPEED){
        this->pider->currentV = -MAX_SPEED;
    }
    //
}

void baseMove(float v1, float v2, float v3, float v4){
  leftforwardMotor.targetV = v1;
  leftbackwardMotor.targetV = v2;
  rightforwardMotor.targetV = v3;
  rightbackwardMotor.targetV = v4;
}

void Forward(float v){
  baseMove(v, v, v, v);
}

void Turn_Back(float v){
  baseMove(-v, -v, -v, -v);
}

void Turn_Left(float v){
  baseMove(-v, -v, v, v);
}

void Turn_Right(float v){
  baseMove(v, v, -v, -v);
}

void Move(){
  //int i;
  // for(i = 0; i < 4; i++){
  //   Base_Motor_Rotate(*(motors+i));
  // }
  Base_Motor_Rotate(&leftforwardMotor);
  Base_Motor_Rotate(&leftbackwardMotor);
  Base_Motor_Rotate(&rightforwardMotor);
  Base_Motor_Rotate(&rightbackwardMotor);
}

int v2pwm(float v){
  //todo: override this function.
  
  if(v > 0){
    return 1400+(int)(v*100);
  }else if(v < 0){
    return 1400+(int)(v*100);
  }
  return 1400;
}

void Stop(){
  leftforwardMotor.targetV = 0.0;
  leftbackwardMotor.targetV = 0.0;
  rightforwardMotor.targetV = 0.0;
  rightbackwardMotor.targetV = 0.0;
}



void Base_Motor_Rotate(MyMotor*const motor){
  //todo: °ÑvÓ³Éäµ½pwm
  //int pwm = (int)motor->targetV*100;
  piControl(motor);
  My_Motor_Rotate(motor, v2pwm(motor->pider->currentV), 1000);
}

void My_Motor_Rotate(MyMotor*const motor, int pwm, int time){
  Motor_Rotate(motor->MotorID, pwm, time);
}