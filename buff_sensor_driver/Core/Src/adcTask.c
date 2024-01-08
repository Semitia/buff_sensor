#include "adcTask.h"

uint16_t i,j;
#define ADC1_CHANNEL_CNT 10
#define ADC1_CHANNEL_FRE 3	
uint16_t adc1_val_buf[ADC1_CHANNEL_CNT*ADC1_CHANNEL_FRE]; 
uint32_t adc1_sum_val[ADC1_CHANNEL_CNT] = {0}; 
uint16_t value[ADC1_CHANNEL_CNT] = {0};

void adcTask(void *argument) {
    if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc1_val_buf, (ADC1_CHANNEL_CNT*ADC1_CHANNEL_FRE)) != HAL_OK) {
        /* Start Conversation Error */
        Error_Handler(); 
    }
    while(1) {
        for(i=0;i<ADC1_CHANNEL_CNT;i++){
            adc1_sum_val[i] = 0;
        }
        for(i=0;i<ADC1_CHANNEL_CNT*ADC1_CHANNEL_FRE;i++){
            j = i%ADC1_CHANNEL_CNT;
            adc1_sum_val[j] += adc1_val_buf[i];
        }
        for(i=0;i<ADC1_CHANNEL_CNT;i++){
            value[i] = adc1_sum_val[i]/ADC1_CHANNEL_FRE;
        }
        osDelay(10);
    }
}

