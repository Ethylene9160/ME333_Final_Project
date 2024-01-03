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
    //����ߵ�ƽ
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

//�ȶ��ڲ࣬�������ȡ��A5
void detectMove(){
  if (digitalRead(&middlemiddleDetector) == FLAG){
    //ǰ��
    Forward(3.35);
  }else if (digitalRead(&leftleftDetector) == FLAG){
    //��ת
    Turn_Large_Left(2.4);
    // base_move(1,1,1,1);
  }else if (digitalRead(&rightrightDetector) == FLAG){
    //��ת
    Turn_Large_Right(2.4);
    // base_move(1,1,1,1);
  }else if (digitalRead(&leftmiddleDetector) == FLAG){
    //��ת
    Turn_Left(2.2);
    // base_move(1,1,1,1);
  }else if (digitalRead(&rightmiddleDetector) == FLAG){
    //��ת
    Turn_Right(2.2);
    // base_move(1,1,1,1);
  }else{
    //ֱ��
    //Forward(2.5);
    // baseMove(3.0,3.0,1.2,1.2);
    baseMove(1.5,-1.5,-1.5,1.5);

  }
}