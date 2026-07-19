#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

extern int16_t Encoder_Count;   // 全局计数变量

int16_t Encoder_GetPWM(void);     // 获取增量值（读取后清零）

#endif
