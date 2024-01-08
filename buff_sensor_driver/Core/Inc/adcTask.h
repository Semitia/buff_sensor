#ifndef __ADCTASK_H
#define __ADCTASK_H
#include "main.h"

// 1~10环 对应的adc采样通道(1~10)
typedef enum {
    Ring6 = 0,
    Ring7,
    Ring8,
    Ring9,
    Ring10,
    Ring5,
    Ring4,
    Ring3,
    Ring2,
    Ring1
} RingNum_e;

void adcTask(void *argument);

#endif // __ADCTASK_H

