
#ifndef MY_MOTOR
#define MY_MOTOR 1
// #endif
// #ifdef MY_MOTOR
#include "usart.h"
#include "gpio.h"
#include"PID.h"

#define MAX_SPEED 2.5//max speed of the car
//define the id of the 4 motors
#define LEFT_FORWARD 2//motor of left forward
#define RIGHT_FORWARD 1//motor of right forward
#define LEFT_BACKWARD 3//motor of left backward
#define RIGHT_BACKWARD 4//motor of right backward
#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    int MotorID;                        //MotorID
    float targetV;
    PIDer* pider;                       //pider
}MyMotor;

extern MyMotor leftforwardMotor, leftbackwardMotor, rightforwardMotor, rightbackwardMotor;
extern PIDer leftforwardPider, leftbackwardPider, rightforwardPider, rightbackwardPider;
void initAllMotors();

/**
 * @brief init motor.
 * 
 * @param this Mymotor instance.
 * @param MotorID the ID of the motor.
 * @param pider no use.
 */
void initMotor(MyMotor* this, int MotorID, PIDer* pider);

/**
 * @brief Deprecated.
 * 
 * @param this 
 * @param targetV 
 */
void smoothControl(MyMotor* this, float targetV);

/**
 * @brief Deprecated.
 * 
 * @param this 
 */
void piControl(MyMotor* this);

/**
 * @brief set the velosity of motors.
 * 
 * @param v1 leftforward motor
 * @param v2 leftbackward motor
 * @param v3 rightforward motor
 * @param v4 rightbackward motor
 */
void baseMove(float v1, float v2, float v3, float v4);

/**
 * @brief rotate the motor 200ms default.
 * 
 * @param motor motor you want to rotate.
 */
void Base_Motor_Rotate(MyMotor* const motor);

/**
 * @brief private function. pass the motor instance and pwm and time, you can rotate the motor.
 * 
 * @param motor MyMotor instance
 * @param pwm pwm.
 * @param time time you want to rotate.
 */
void My_Motor_Rotate(MyMotor* const motor, int pwm, int time);

/**
 * @brief Move all motors.
 * 
 * @param time time you want to move. eg. time=200 <-> 200ms.
 */
void TimeMove(int time);

//注意，下面的四个函数，只会修改电机的速度，不会马上转动电机。
void Turn_Left(float v);

void Turn_Right(float v);

void Turn_Back(float v);

void Forward(float v);

void Stop();

//需要调用下面的函数，才会真正转动电机。
/**
 * @brief Call Move or TimeMove can rotate the motors.
 * Defaiult: 200s.To change this default valut, see @Base_Motor_Rotate(MyMotor*const motor).
 */
void Move();

/**
 * @brief transform the velosity to pwm.
 * 
 * @param v velosity
 * @return int pwm
 */
int v2pwm(float v);

//"private" methods


void private_Base_Motor_Rotate(MyMotor*const motor, int time);

#ifdef __cplusplus
}
#endif

#endif
