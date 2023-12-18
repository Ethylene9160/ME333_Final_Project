#ifndef MY_DETECTOR_H
#define MY_DETECTOR_H 1
#include "main.h"
#include "MyMotor.h"
#include "stm32f767xx.h"


#define FLAG 0
#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    uint32_t pin;
    GPIO_TypeDef* port;
}MyDetector;

// TODO: change the pin!!!
// #define LEFT_LEFT 0
// #define LEFT_MIDDLE GPIO_PIN_4
// #define MIDDLE_MIDDLE 
// #define RIGHT_MIDDLE 3
// #define RIGHT_RIGHT 4

#define LEFTLEFT GPIO_PIN_4
#define LEFTMIDDLE GPIO_PIN_4
#define MIDDLEMIDDLE GPIO_PIN_5
#define RIGHTMIDDLE GPIO_PIN_8
#define RIGHTRIGHT GPIO_PIN_6

extern MyDetector leftleftDetector, leftmiddleDetector, middlemiddleDetector, rightmiddleDetector, rightrightDetector;
void initDetector(MyDetector *detector, uint32_t pin, GPIO_TypeDef* port);

uint8_t digitalRead(MyDetector *detector);

void detectMove();

void initAllDetectors();

#ifdef __cplusplus
}
#endif

#endif