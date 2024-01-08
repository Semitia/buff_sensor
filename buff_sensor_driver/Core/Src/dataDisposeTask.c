#include "dataDisposeTask.h"

void change_id(u16 id){
    sensor_ID = id;
    STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)id,2);//覆盖写入新的ID
    return;
}

// 1~10环 对应的adc采样通道(1~10)
const uint8_t adcChannel[11] = {10,9,8,7,6,5,0,1,2,3,4};
TickType_t last_zero_time[11] = {0,0,0,0,0,0,0,0,0,0,0}; //最近的未被击中的时间戳
u16 ring_state = 0; //第i位对应第i环，0:没被击中，1:被击中
u8 ring_state_msg[2];
void dataDisposeTask(void *argument) {
    u8 i;
    while (1){
        for(i=1; i<11; i++){
            if(value[adcChannel[i]] > THRESHOLD ) { //击中
                ring_state |= (1<<i);
                TickType_t now = xTaskGetTickCount();
                if(now - last_zero_time[i] > 3000) { //被连续按压3s以上
                    change_id(i);
                } 
            }
            else {
                ring_state &= ~(1<<i);
                last_zero_time[i] = xTaskGetTickCount();
            }
        }
        ring_state_msg[0] = (ring_state >> 8) & 0xff;
        ring_state_msg[1] = ring_state & 0xff;
        sendCanMsg(ring_state_msg, 2);
        osDelay(10);
    }
}

