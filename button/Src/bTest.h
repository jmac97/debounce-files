#include <stdint.h>
#include "stm32g070xx.h"

#define KEY_PRESSED keyCode != 0x00
#define DEBOUNCE_NUMBER 5
#define REPEAT_TIME 3
#define LONG_HOLD_TIME 100
#define SHORT_HOLD_TIME 50

#define LONG_HOLD 3;
#define SHORT_HOLD 2;
#define PRESS 1;

extern uint8_t keyCode;
extern uint8_t buttonCounter;
extern uint16_t buttonHoldCounter;
extern uint8_t buttonRepeatCounter;
extern uint8_t valid;
extern uint8_t hold;

extern uint8_t lastKeyCode;
extern uint8_t keyProcessed;
extern uint8_t holdVal;

uint8_t GetButtonVal(void);
uint8_t ValidKeyCode(uint8_t val);
uint8_t ProcessKeyCode(uint8_t val);
void ProcessKeyHold(uint8_t val);
void ButtonInit(GPIO_TypeDef* port, uint16_t pin);
void PollKey(void);