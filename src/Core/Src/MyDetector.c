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

uint8_t digitalRead(MyDetector *detector){
    //����ߵ�ƽ
    return HAL_GPIO_ReadPin(detector->port, detector->pin);
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

//�ȶ��ڲ࣬�������ȡ��
void detectMove(){
  // uint8_t flag = 0b00000;
  // flag = flag | (digitalRead(&leftleftDetector)<<4);
  // flag = flag | (digitalRead(&leftmiddleDetector) << 3);
  // flag = flag | (digitalRead(&middlemiddleDetector) << 2);
  // flag = flag | (digitalRead(&rightmiddleDetector) << 1);
  // flag = flag | (digitalRead(&rightrightDetector));
  // printf("flag: %d\n", flag);

  // //ֱ���ڼĴ�������������������Ч�ʡ�
  // uint8_t leftFlag = flag>>3;       //�������λ�ʹθ�λ�����������������
  // uint8_t rightFlag = flag&0b00011; //�������λ�ʹε�λ���ұ�������������

  uint8_t leftFlag = digitalRead(&leftmiddleDetector);       //�������λ�ʹθ�λ�����������������
  leftFlag = leftFlag | (digitalRead(&leftleftDetector)<<1);
  uint8_t rightFlag = digitalRead(&rightrightDetector); //�������λ�ʹε�λ���ұ�������������
  rightFlag = rightFlag | (digitalRead(&rightmiddleDetector)<<1);
  if(isLarge(leftFlag, rightFlag)){
    //��ת
    Turn_Left(2.0);
  }else if(isLarge(rightFlag, leftFlag)){
    //��ת
    Turn_Right(2.0);
  }else{
    //ֱ��
    Forward(2.0);
  }
  // if(leftFlag && !rightFlag){
  //   //��ת
  //   Turn_Left(2.0);
  // }else if(!leftFlag && rightFlag){
  //   //��ת
  //   Turn_Right(2.0);
  // }else{
  //   //ֱ��
  //   Forward(2.0);
  // }
  return;
  switch (flag)
  {
  case 0b00000:
  case 0b00100:
  case 0b01110:
  case 0b11111:
  case 0b01010:
  case 0b10001:
  case 0b11011:
    //ֱ��
    Forward(2.0);
    break;
  case 0b00001:
  case 0b00011:
  case 0b00001:
    //��ת
    Turn_Left(2.0);
    Turn_Left(2.0);
    break;
  case 0b01000:
  case 0b11000:
  case 0b10000:
    Turn_Right(2.0);
    break;
  default:
    //ֱ��
    Forward(2.0);
    break;
  }

  // if (digitalRead(&middlemiddleDetector) == FLAG){
  //   //ǰ��
  //   Forward(2.0);
  // }else if (digitalRead(&leftmiddleDetector) == FLAG){
  //   //��ת
  //   Turn_Left(2.0);
  // }else if (digitalRead(&rightmiddleDetector) == FLAG){
  //   //��ת
  //   Turn_Right(2.0);
  // }else if (digitalRead(&leftleftDetector) == FLAG){
  //   //��ת
  //   Turn_Left(2.0);
  // }else if (digitalRead(&rightrightDetector) == FLAG){
  //   //��ת
  //   Turn_Right(2.0);
  // }else{
  //   //ֱ��
  //   Forward(2.0);
  // }
}