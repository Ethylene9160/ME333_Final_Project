#ifndef MY_DETECTOR_H
#define MY_DETECTOR_H 1
// #endif
// #ifdef MY_DETECTOR_H
#include "main.h"
#include "MyMotor.h"
#include "stm32f767xx.h"


#define FLAG 0
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MyDetector, a struct store the infomation of a detector, pin and GPIO type.
 *  For example, if you want to use PA0, you can use this struct to store the infomation as:
 *  MyDetector detector;
 *  detetor.pin = GPIO_PIN_0;
 *  detector.port = GPIOA;
 * @author @Ethylene9160
 */
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

//This should be defined in main.c!!!
extern MyDetector leftleftDetector, leftmiddleDetector, middlemiddleDetector, rightmiddleDetector, rightrightDetector;

/**
 * @brief init the detector.
 * 
 * @param detector detector structure instance you want to init.
 * @param pin pin of the detector, like "GPIN_PIN_0".
 * @param port GPIO type, like "GPIOA".
 */
void initDetector(MyDetector *detector, uint32_t pin, GPIO_TypeDef* port);

/**
 * @brief read the detector result.
 *  If black detected, then low level returned; if white detected, then high level returned.
 * 
 * @param detector detector instance.
 * @return uint8_t level of the detector result, high if white, low if black.
 */
uint8_t digitalRead(MyDetector *detector);

/**
 * @brief Immortal search function. See function body ples.
 */
void detectMove();

/**
 * @brief init all the detectors. See function body ples.
 * 
 */
void initAllDetectors();

#ifdef __cplusplus
}
#endif

#endif