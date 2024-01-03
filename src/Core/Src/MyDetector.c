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
    //����ߵ��?
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

uint8_t isLarge(uint8_t a, uint8_t b){
  uint8_t A = a>>1, B = a&0b01;
  uint8_t C = b>>1, D = b&0b01;
  return (B&(!C)&(!D))|(A&(!C))|(A&B&(!D));  
}

//�ȶ��ڲ࣬�������ȡ��A
void detectMove(){
  uint8_t ll = !digitalRead(&leftleftDetector);
  uint8_t lm = !digitalRead(&leftmiddleDetector);
  uint8_t mm = !digitalRead(&middlemiddleDetector);
  uint8_t rm = !digitalRead(&rightmiddleDetector);
  uint8_t rr = !digitalRead(&rightrightDetector);
  // uint8_t flag = 0b00000;
  // flag |= ll <<4;
  // flag |= lm <<3;
  // flag |= mm <<2;
  // flag |= rm <<1;
  // flag |= rr;
  if(mm){
    // if(lm){
    //   diffMove(1.9,3.45);
    // }else if(rm){
    //   diffMove(3.45,1.9);
    // }else{
    //   Forward(3.8);
    // }
    Forward(3.0);
  }else if(lm){
    diffMove(1.6,3.0);
  }else if(ll){
    diffMove(1.4,2.9);
  }else if(rm){
    if(rr){
      diffMove(3.2,1.61);
    }else{
      diffMove(3.6,2.45);
    }
  }else if(rr){
    diffMove(3.25,1.35);
  }else{
    diffMove(3.1,1.33);
  }
  // switch (flag)
  // {
  // case 0b00001:
  //   diffMove(2.2,-1.25);
  //   break;
  // case 0b00010:
  // case 0b00011:
  //   diffMove(3.5,1.9);
  //   break;
  // //case 0b00010:
  // case 0b00110:
  // case 0b00111:
  //   diffMove(3.5,2.25);
  //   break;
  // case 0b00100:
  //   Forward(3.5);
  // case 0b
  // default:
  //   break;
  // }
  // if(digitalRead(&middlemiddleDetector)){
  //   if(digitalRead(&rightmiddleDetector)){
  //     diffMove(2.2,3.5);
  //   }else if(digitalRead(&leftmiddleDetector)){
  //     diffMove(3.5,2.2);
  //   }else{
  //     Forward(3.5);
  //   }
  // }
  // else if(digitalRead(&rightrightDetector)){
  //   if(digitalRead(&rightmiddleDetector)){
  //     diffMove(3.3,1.5);
  //   }else{
  //     diffMove(1.55,-1.32);
  //   }
  // }else if(digitalRead(&leftleftDetector)){
  //   if(digitalRead(&leftmiddleDetector)){
  //     diffMove(1.5,3.3);
  //   }else{
  //     diffMove(-1.32,1.55);
  //   }
  // }
  // else{
  //   if(digitalRead(&rightmiddleDetector)){
  //     diffMove(3.3,1.8);
  //   }else if(digitalRead(&leftmiddleDetector)){
  //     diffMove(1.8,3.3);
  //   }else{
  //     diffMove(2.0,-1.25);
  //   }
  // }
}