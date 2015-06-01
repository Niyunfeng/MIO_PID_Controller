#ifndef __PWM__
#define __PWM__

/*******************************************************************************
* Function Name  : None
* Description    : ��ʱ��3 PWM���ռ�ձ�ȫ�ֱ��� 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 4

/*******************************************************************************
* Function Name  : TIM3PWM_4Channel_Configuration
* Description    : ��ʼ����ʱ��3��4��ͨ����PWM�����ռ�ձȳ�ʼ��Ϊ50% 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3PWM_4Channel_Configuration(void);

/*******************************************************************************
* Function Name  : Adjust_DutyCycle
* Description    : ��ʱ��3����4��ͨ����ռ�ձ� 
* Input          : CHx : ���ͨ��   DC : ���ڵ�������
* Output         : None
* Return         : None
*******************************************************************************/
void Adjust_TIM3DutyCycle(unsigned char CHx , unsigned int DC);

#endif

