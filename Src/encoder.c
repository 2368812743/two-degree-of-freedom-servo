#include "encoder.h"

/* 舵机PWM边界值（根据你的定时器配置：PSC=71, ARR=20000）*/
#define PWM_MIN    500    // 对应 0°
#define PWM_MAX    2500   // 对应 180°
#define PWM_STEP   50     // 每次编码器旋转变化的步进值

int16_t Encoder_Count = 1500;  // 初始值：90° 中间位置

/**
  * @brief  获取编码器增量值（读取后自动清零）
  * @param  无
  * @retval 当前编码器计数值（已限幅）
  */
int16_t Encoder_Get(void)
{
    return Encoder_Count;
}

/**
  * @brief  直接获取PWM比较值（带边界保护）
  * @param  无
  * @retval 限幅后的PWM比较值（范围：500 ~ 2500）
  */
int16_t Encoder_GetPWM(void)
{
    /* 边界限幅保护 */
    if(Encoder_Count > PWM_MAX)
    {
        Encoder_Count = PWM_MAX;
    }
    else if(Encoder_Count < PWM_MIN)
    {
        Encoder_Count = PWM_MIN;
    }
    
    return Encoder_Count;
}

/**
  * @brief  EXTI 回调函数（由 HAL 库的中断服务函数调用）
  * @param  GPIO_Pin: 触发中断的引脚
  * @retval 无
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* 防止编译警告（参数未使用） */
    UNUSED(GPIO_Pin);
    
    /* 处理 A 相中断 (PB11) */
    if(GPIO_Pin == encoderA_Pin)
    {
        /* 判断当前A相是否为低电平（下降沿有效） */
        if(HAL_GPIO_ReadPin(encoderA_GPIO_Port, encoderA_Pin) == GPIO_PIN_RESET)
        {
            /* 检测B相电平判断方向 */
            if(HAL_GPIO_ReadPin(encoderB_GPIO_Port, encoderB_Pin) == GPIO_PIN_RESET)
            {
                /* 正转：数值增大，但不得高于上限 */
                if(Encoder_Count < PWM_MAX)
                {
                    Encoder_Count += PWM_STEP;
                    if(Encoder_Count > PWM_MAX)
                    {
                        Encoder_Count = PWM_MAX;  // 上限钳位
                    }
                }
            }
        }
    }
    
    /* 处理 B 相中断 (PB10) */
    if(GPIO_Pin == encoderB_Pin)
    {
        /* 判断当前B相是否为低电平（下降沿有效） */
        if(HAL_GPIO_ReadPin(encoderB_GPIO_Port, encoderB_Pin) == GPIO_PIN_RESET)
        {
            /* 检测A相电平判断方向 */
            if(HAL_GPIO_ReadPin(encoderA_GPIO_Port, encoderA_Pin) == GPIO_PIN_RESET)
            {
                /* 反转：数值减小，但不得低于下限 */
                if(Encoder_Count > PWM_MIN)
                {
                    Encoder_Count -= PWM_STEP;
                    if(Encoder_Count < PWM_MIN)
                    {
                        Encoder_Count = PWM_MIN;  // 下限钳位
                    }
                }
            }
        }
    }
}