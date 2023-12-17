#include"MyDetector.h"

void initDetector(MyDetector *detector, uint32_t pin){
    detector->pin = pin;
    //todo: init the pin
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

u8 digitalRead(MyDetector *detector){
    //捕获高电平
    return HAL_GPIO_ReadPin(GPIOB, detector->pin);
}