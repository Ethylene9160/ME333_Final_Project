#ifndef MY_DETECTOR_H
#define MY_DETECTOR_H 1
#include "main.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    uint32_t pin;
    GPIO_TypeDef* port;
}MyDetector;

// TODO: change the pin!!!
#define LEFT_LEFT 0
#define LEFT_MIDDLE 1
#define MIDDLE_MIDDLE 2
#define RIGHT_MIDDLE 3
#define RIGHT_RIGHT 4

void initDetector(MyDetector *detector, uint32_t pin, GPIO_TypeDef* port);

uint8_t digitalRead(MyDetector *detector);

#ifdef __cplusplus
}
#endif

#endif