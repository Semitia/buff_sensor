#include "dataDisposeTask.h"

void change_id(u16 id){
    sensor_ID = id;
    STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)&id,2);//覆盖写入新的ID
    return;
}

// 1~10环 对应的adc采样通道(1~10)
const uint8_t adcChannel[11] = {10,0,1,2,3,4,9,8,7,6,5};
TickType_t last_zero_time[11] = {0,0,0,0,0,0,0,0,0,0,0}; //最近的未被击中的时间戳
u16 ring_state = 0; //第i位对应第i环，0:没被击中，1:被击中
u8 ring_state_msg[2];
u8 change_id_flag = 0;
void dataDisposeTask(void *argument) {
    u8 i;
    while (1){
        for(i=1; i<11; i++){
            if(value[adcChannel[i]] > THRESHOLD ) { //击中
                ring_state |= (1<<i);
                TickType_t now = xTaskGetTickCount();
                if((now - last_zero_time[i] > 3000) && (!change_id_flag)) { //被连续按压3s以上
                    change_id(i);
                    change_id_flag = 1;
                } 
            }
            else {
                ring_state &= ~(1<<i);
                last_zero_time[i] = xTaskGetTickCount();
                change_id_flag = 0;
            }
        }
        ring_state_msg[0] = (ring_state >> 8) & 0xff;
        ring_state_msg[1] = ring_state & 0xff;
        //sendCanMsg(ring_state_msg, 2);
				CAN_SendState(ring_state_msg, 2);
        osDelay(10);
    }
}

/* flash测试 */
// const u8 TEXT_Buffer_1[]={"STM32 FLASH TEST_1"};//要写入到STM32 FLASH的字符串数组
// const u8 TEXT_Buffer_2[]={"STM32 FLASH TEST_2"};//要写入到STM32 FLASH的字符串数组
// #define SIZE sizeof(TEXT_Buffer_1)	 	//数组长度

// void dataDisposeTask(void *argument) {
//     u8 datatemp[SIZE];  //Flash读取缓存数组

//     STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer_1,SIZE);//第一次写读
//     STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);

//     osDelay(1000);
//     STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer_2,SIZE);//第二次写读    
//     STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);


//     while (1){
//     }
// }
