#include"MyDetector.h"

void initDetector(MyDetector *detector, uint32_t pin, GPIO_TypeDef* port){
    detector->pin = pin;
    detector->port = port;
    //port = GPIO_PIN_5;//GPIO_PIN_5
    //todo: init the pin
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(detector->port, &GPIO_InitStruct);
}

inline uint8_t digitalRead(MyDetector *detector){
    //??
    // GPIO_PinState bitstatus;

    /* Check the parameters */
    //assert_param(IS_GPIO_PIN(GPIO_Pin));
    return (detector->port->IDR & detector->pin) != (uint32_t)GPIO_PIN_RESET;

    // if((detector->port->IDR & detector->pin) != (uint32_t)GPIO_PIN_RESET)
    // {
    //   bitstatus = GPIO_PIN_SET;
    // }
    // else
    // {
    //   bitstatus = GPIO_PIN_RESET;
    // }
    // return bitstatus;

    //return HAL_GPIO_ReadPin(detector->port, detector->pin);
}

void initAllDetectors(){
  initDetector(&leftleftDetector, GPIO_PIN_4, GPIOB);
  initDetector(&leftmiddleDetector, GPIO_PIN_6,GPIOA);
  initDetector(&middlemiddleDetector,GPIO_PIN_7 ,GPIOA);
  initDetector(&rightmiddleDetector, GPIO_PIN_8,GPIOB);
  initDetector(&rightrightDetector, GPIO_PIN_6,GPIOB);
}


//????A5
void detectMove(){
  if (digitalRead(&middlemiddleDetector) == FLAG){
    //?
    Forward(3.3);
  }else if (digitalRead(&leftleftDetector) == FLAG){
    //?
    Turn_Large_Left(2.4);
    // base_move(1,1,1,1);
  }else if (digitalRead(&rightrightDetector) == FLAG){
    //?
    Turn_Large_Right(2.4);
    // base_move(1,1,1,1);
  }else if (digitalRead(&leftmiddleDetector) == FLAG){
    //?
    Turn_Left(2.2);
    // base_move(1,1,1,1);
  }else if (digitalRead(&rightmiddleDetector) == FLAG){
    //?
    Turn_Right(2.6);
    // base_move(1,1,1,1);
  }else{
    //?
    //Forward(2.5);
    // baseMove(3.0,3.0,1.2,1.2);
    baseMove(1.7,-1.3,-1.3,1.7);
  }
}