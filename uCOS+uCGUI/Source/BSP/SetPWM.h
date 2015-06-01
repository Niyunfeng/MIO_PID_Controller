#ifndef __SETPWM
#define __SETPWM

#include "includes.h"




#define PWM_PB0_CH3    3
#define PWM_BACK_LIGHT 4

#define PWM_PB9_CH4  5
#define PWM_PB8_CH3  6


#define BRIGHT_MAX		255		/* ������� */
#define BRIGHT_MIN		0		/* ��С����,��������Ϊ0 */
#define BRIGHT_DEFAULT	200		/* ȱʡ���� */

/* 2 PWM: BkLight(PB1) PWM_PB0_CH3 */
void SetPWM(unsigned short _bright,unsigned int PWM_CH);

/* 2 PWM: (PB6) (PB7) */
void SetPWM_TIM4(unsigned short _bright,unsigned int PWM_CH);

#endif
