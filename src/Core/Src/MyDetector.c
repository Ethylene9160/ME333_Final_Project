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
    //捕获高电平
    return HAL_GPIO_ReadPin(detector->port, detector->pin);
}

void initAllDetectors(){
  initDetector(&leftleftDetector, LEFTLEFT, GPIOB);
  initDetector(&leftmiddleDetector, LEFTMIDDLE,GPIOA);
  initDetector(&middlemiddleDetector,MIDDLEMIDDLE ,GPIOA);
  initDetector(&rightmiddleDetector, RIGHTMIDDLE,GPIOB);
  initDetector(&rightrightDetector, RIGHTRIGHT,GPIOB);
}

//先读内侧，再往外读取。
void detectMove(){
  if (digitalRead(&middlemiddleDetector) == FLAG){
    //前进
    Forward(2.0);
  }else if (digitalRead(&leftmiddleDetector) == FLAG){
    //左转
    Turn_Left(2.0);
  }else if (digitalRead(&rightmiddleDetector) == FLAG){
    //右转
    Turn_Right(2.0);
  }else if (digitalRead(&leftleftDetector) == FLAG){
    //左转
    Turn_Left(2.0);
  }else if (digitalRead(&rightrightDetector) == FLAG){
    //右转
    Turn_Right(2.0);
  }else{
    //直走
    Stop();
  }
}