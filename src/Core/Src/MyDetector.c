#include"MyDetector.h"

void initDetector(MyDetector *detector, uint32_t pin, GPIO_TypeDef* port){
    detector->pin = pin;
    detector->port = port;
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