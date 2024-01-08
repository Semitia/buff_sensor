#ifndef __ADCTASK_H
#define __ADCTASK_H
#include "main.h"

#define ADC1_CHANNEL_CNT 10
#define ADC1_CHANNEL_FRE 3	

extern uint16_t value[ADC1_CHANNEL_CNT];
void adcTask(void *argument);

#endif // __ADCTASK_H

