#include"MyDetector.h"

void initDetector(MyDetector *detector, uint32_t pin, GPIO_TypeDef* port){
    detector->pin = pin;
    detector->port = port;
    //port = GPIO_PIN_5;//GPIO_PIN_5
    //todo: init the pin
    // GPIO_InitTypeDef GPIO_InitStruct;
    // GPIO_InitStruct.Pin = pin;
    // GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(detector->port, &GPIO_InitStruct);
}

uint8_t digitalRead(MyDetector *detector){
    //����ߵ�ƽ
    return HAL_GPIO_ReadPin(detector->port, detector->pin);
}

void initAllDetectors(){
  initDetector(&leftleftDetector, LEFTLEFT, GPIOB);
  initDetector(&leftmiddleDetector, LEFTMIDDLE,GPIOA);
  initDetector(&middlemiddleDetector,MIDDLEMIDDLE ,GPIOA);
  initDetector(&rightmiddleDetector, RIGHTMIDDLE,GPIOB);
  initDetector(&rightrightDetector, RIGHTRIGHT,GPIOB);
}

//�ȶ��ڲ࣬�������ȡ��
void detectMove(){
  if (digitalRead(&middlemiddleDetector) == FLAG){
    //ǰ��
    Forward(2.0);
  }else if (digitalRead(&leftmiddleDetector) == FLAG){
    //��ת
    Turn_Left(2.0);
  }else if (digitalRead(&rightmiddleDetector) == FLAG){
    //��ת
    Turn_Right(2.0);
  }else if (digitalRead(&leftleftDetector) == FLAG){
    //��ת
    Turn_Left(2.0);
  }else if (digitalRead(&rightrightDetector) == FLAG){
    //��ת
    Turn_Right(2.0);
  }else{
    //ֱ��
    Stop();
  }
}