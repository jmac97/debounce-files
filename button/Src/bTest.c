#include "bTest.h"
#include "main.h"
#include <stdio.h>

uint8_t keyCode = 0x0;
uint8_t buttonCounter = 5;
uint16_t buttonHoldCounter = 0;
uint8_t buttonRepeatCounter = 0;

uint8_t volatile repeatCounter = 0;
uint8_t volatile holdCounter = 0;
uint8_t volatile pressCounter = 0;

uint8_t holdVal = 0;
uint8_t lastKeyCode = 0x0;
uint8_t keyProcessed = false;

uint8_t pinState = 1;

uint8_t GetButtonVal(void) 
{
  uint8_t bVal = 0x0;
  
  if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) {
    bVal = bVal | 0x1;
  }
  
  return bVal;
}

uint8_t ProcessKeyCode(uint8_t val) {
  switch (val) {
  case 0x01:
    switch (holdVal) {
      case 1:
        pressCounter++;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, pinState);
        pinState = !pinState;
        break;
      case 2:
        holdCounter++;
        break;
      case 3:
        repeatCounter++;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, pinState);
        pinState = !pinState;
        break;
    }
    break;
  }
  return true;
}

