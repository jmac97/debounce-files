#include "bTest.h"
#include "main.h"
#include <stdio.h>

uint8_t keyCode = 0x0;
uint8_t buttonCounter = 5;
uint16_t buttonHoldCounter = 0;
uint8_t buttonRepeatCounter = 0;

uint8_t holdVal = 0;
uint8_t lastKeyCode = 0x0;
uint8_t keyProcessed = false;

uint16_t buttonPin;
GPIO_TypeDef* buttonPort;

extern uint8_t tenMsFlag;

void ButtonInit(GPIO_TypeDef* port, uint16_t pin) {
  buttonPort = port;
  buttonPin = pin;
}

uint8_t GetButtonVal(void) 
{
  uint8_t bVal = 0x0;
  
  if (!HAL_GPIO_ReadPin(buttonPort, buttonPin)) {
    bVal = bVal | 0x1;
  }
  
  return bVal;
}

uint8_t ProcessKeyCode(uint8_t val) {
  switch (val) {
  case 0x01:
    switch (holdVal) {
      case 1:
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        break;
      case 2:
        for (uint8_t i = 0; i <= 9; i++) {
          HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
          HAL_Delay(250);
        }
        break;
      case 3:
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        break;
    }
    break;
  }
  return true;
}

void PollKey(void) {
  if (tenMsFlag) {
    tenMsFlag = false;
    keyCode = GetButtonVal();
    
    if (KEY_PRESSED) {
      if (keyCode == lastKeyCode) {
        if (buttonCounter != 0) {
          buttonCounter--;
        } else {
          if (buttonHoldCounter <= LONG_HOLD_TIME) {
            buttonHoldCounter++;
          } else {
            buttonRepeatCounter--;
            if (buttonRepeatCounter == 0) {
              holdVal = LONG_HOLD;
              ProcessKeyCode(keyCode);
              buttonRepeatCounter = REPEAT_TIME;
              holdVal = 0;
            }
          }
        }
      } else {
        lastKeyCode = keyCode;
      }
    } else {
      if (buttonHoldCounter >= SHORT_HOLD_TIME && buttonHoldCounter <= LONG_HOLD_TIME) {
        holdVal = SHORT_HOLD;
      } else if (buttonCounter == 0 && buttonHoldCounter < SHORT_HOLD_TIME) {
        holdVal = PRESS;
      } else {
        holdVal = 0;
      }
      
      ProcessKeyCode(lastKeyCode);
      buttonCounter = DEBOUNCE_NUMBER;
      buttonHoldCounter = 0;
      buttonRepeatCounter = REPEAT_TIME;
    }
  }
}

