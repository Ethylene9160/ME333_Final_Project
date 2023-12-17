#ifndef MY_DETECTOR_H
#define MY_DETECTOR_H 1
#include "stm32f7xx_hal_gpio.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    uint32_t pin;
    
}MyDetector;

#define LEFT_LEFT 0
#define LEFT_MIDDLE 1
#define MIDDLE_MIDDLE 2
#define RIGHT_MIDDLE 3
#define RIGHT_RIGHT 4

void initDetector(MyDetector *detector, int pin);

u8 digitalRead(MyDetector *detector);

#ifdef __cplusplus
}
#endif

#endif