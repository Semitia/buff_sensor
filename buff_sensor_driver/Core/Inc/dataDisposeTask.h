#ifndef __DATA_DISPOSE_TASK_H__
#define __DATA_DISPOSE_TASK_H__
#include "flash.h"
#include "adcTask.h"

#define THRESHOLD 100 // 判断是否被击中的阈值电压 3.3/4096mv

void dataDisposeTask(void *argument);

#endif // __DATA_DISPOSE_TASK_H__

