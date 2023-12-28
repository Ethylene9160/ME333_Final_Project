#include"MyMotor.h"
void initMotor(MyMotor* this, int MotorID, PIDer* pider){
    this->MotorID = MotorID;
    this->targetV = 0.0;
    this->pider = pider;
}

void initAllMotors(){
    //todo: adjust pid
    initPID(&leftforwardPider, 1.2, 0.1, 0.0);
    initPID(&leftbackwardPider, 1.2, 0.1, 0.0);
    initPID(&rightforwardPider, 1.2, 0.1, 0.0);
    initPID(&rightbackwardPider, 1.2, 0.1, 0.0);

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
    // static float step = 0.1;
    // if(this->targetV > this->pider->currentV){
    //     this->pider->currentV += step;
    // }else if(this->targetV < this->pider->currentV){
    //     this->pider->currentV -= step;
    // }
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
  baseMove(0.5*v, 0.5*v, 1.1*v, 1.1*v);
}

void Turn_Large_Left(float v){
  baseMove(-0.6*v, -0.6*v, v, v);
}

void Turn_Large_Right(float v){
  baseMove(-0.6*v, -0.6*v, v, v);
}

void Turn_Right(float v){
  baseMove(1.1*v, 1.1*v, 0.5*v, 0.5*v);
}

//default: 1s.
void Move(){
  //int i;
  // for(i = 0; i < 4; i++){
  //   Base_Motor_Rotate(*(motors+i));
  // }
  Base_Motor_Rotate(&leftforwardMotor);
  Base_Motor_Rotate(&leftbackwardMotor);
  Base_Motor_Rotate(&rightforwardMotor);
  Base_Motor_Rotate(&rightbackwardMotor);
  // TimeMove(1000);
}

void TimeMove(int time){
  private_Base_Motor_Rotate(&leftforwardMotor, time);
  private_Base_Motor_Rotate(&leftbackwardMotor, time);
  private_Base_Motor_Rotate(&rightforwardMotor, time);
  private_Base_Motor_Rotate(&rightbackwardMotor, time);
}

int v2pwm(float v){
  //todo: override this function.
  
  if(v > 0){
    return 1400+(int)(v*250);
  }else if(v < 0){
    return 1400+(int)(v*250);
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
    // int i;
    // for(i = 0; i < 40; ++i){
    //     piControl(motor);
    //     My_Motor_Rotate(motor, v2pwm(motor->pider->currentV), 20);
    // }
    // In fact, we do not have any speed encoder, 
    // so after the motor is rotated, we need to force set the current velosity
    // to the target velosity, 
    // and leave enough time for the motor to run into the stable state.
    motor->pider->currentV = motor->targetV;
    My_Motor_Rotate(motor, v2pwm(motor->pider->currentV), 200);
}

//Deprecated
void private_Base_Motor_Rotate(MyMotor*const motor, int time){
    // int i;
    // int period = 20;
    // int i_max = time / period-4;
    
    // for(i = 0; i < i_max; ++i){
    //     piControl(motor);
    //     My_Motor_Rotate(motor, v2pwm(motor->pider->currentV), period);
    // }
    // In fact, we do not have any speed encoder, 
    // so after the motor is rotated, we need to force set the current velosity
    // to the target velosity, 
    // and leave enough time for the motor to run into the stable state.
    motor->pider->currentV = motor->targetV;
    My_Motor_Rotate(motor, v2pwm(motor->pider->currentV), time);
}

void My_Motor_Rotate(MyMotor*const motor, int pwm, int time){
    Motor_Rotate(motor->MotorID, pwm, time);
}