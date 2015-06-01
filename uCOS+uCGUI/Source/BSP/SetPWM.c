#include "includes.h"
#include "SetPWM.h"


/*
*********************************************************************************************************
*	�� �� ��: SetPWM
*	����˵��: ��ʼ��GPIO,����ΪPWMģʽ
*	��    �Σ�_bright ���ȣ�0����255������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SetPWM(unsigned short _bright,unsigned int PWM_CH)
{
	/*
		��������� PB1, ���ù���ѡ�� TIM3_CH4
	
		���رձ���ʱ����CPU IO����Ϊ��������ģʽ���Ƽ�����Ϊ������������������͵�ƽ)
		��TIM3�ر��Խ�Լ����
	*/

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* ��1������GPIOB RCC_APB2Periph_AFIO ��ʱ��	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	if(PWM_BACK_LIGHT == PWM_CH)
	{		
			if (_bright == 0)
			{
				/* ���ñ���GPIOΪ����ģʽ */
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);

				/* �ر�TIM3 */
				TIM_Cmd(TIM3, DISABLE);
				return;
			}
			else if (_bright == BRIGHT_MAX)	/* ������� */
			{
				/* ���ñ���GPIOΪ�������ģʽ */
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);

				GPIO_SetBits(GPIOB, GPIO_Pin_1);

				/* �ر�TIM3 */
				TIM_Cmd(TIM3, DISABLE);
				return;
			}
	}
	
	/* Configure the PIN */
	{
		{
			/* ���ñ���GPIOΪ�����������ģʽ */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			/* ʹ��TIM3��ʱ�� */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		}
		
		{
			/* ���ñ���GPIOΪ�����������ģʽ */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* ʹ��TIM3��ʱ�� */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		}
	}
	
	{
		/*
			TIM3 ����: ����2·PWM�ź�;
			TIM3CLK = 72 MHz, Prescaler = 0(����Ƶ), TIM3 counter clock = 72 MHz
			���㹫ʽ��
			PWM���Ƶ�� = TIM3 counter clock /(ARR + 1)

			������������Ϊ100Hz

			�������TIM3CLKԤ��Ƶ����ô�����ܵõ�100Hz��Ƶ��
			�������÷�Ƶ�� = 1000�� ��ô  TIM3 counter clock = 72KHz
			TIM_Period = 720 - 1;
			Ƶ���²�����
		 */
		TIM_TimeBaseStructure.TIM_Period = 720 - 1;	/* TIM_Period = TIM3 ARR Register */
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

		/* PWM1 Mode configuration */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;// ���ģʽ
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	}	

	/*
		_bright = 1 ʱ, TIM_Pulse = 1
		_bright = 255 ʱ, TIM_Pulse = TIM_Period
	*/
	
	if(PWM_BACK_LIGHT == PWM_CH)
	{
		TIM_OCInitStructure.TIM_Pulse = (TIM_TimeBaseStructure.TIM_Period * _bright) / BRIGHT_MAX;	/* �ı�ռ�ձ� */

		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	}
	
	if(PWM_PB0_CH3 == PWM_CH)
	{
		TIM_OCInitStructure.TIM_Pulse = (TIM_TimeBaseStructure.TIM_Period * _bright) / BRIGHT_MAX;	/* �ı�ռ�ձ� */

		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	}
	
	
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}


/*
*********************************************************************************************************
*	�� �� ��: SetPWM_TIM4
*	����˵��: ��ʼ��GPIO,����ΪPWMģʽ
*	��    �Σ�_bright ���ȣ�0����255������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SetPWM_TIM4(unsigned short _bright,unsigned int PWM_CH)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* ��1������GPIOB RCC_APB2Periph_AFIO ��ʱ��	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);


	
	/* Configure the PIN */
	{
		/* ���ñ���GPIOΪ�����������ģʽ */
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* ʹ��TIM3��ʱ�� */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
		
			
	{
		/*
			TIM4 ����: ����2·PWM�ź�;
			TIM3CLK = 72 MHz, Prescaler = 0(����Ƶ), TIM3 counter clock = 72 MHz
			���㹫ʽ��
			PWM���Ƶ�� = TIM3 counter clock /(ARR + 1)

			������������Ϊ100Hz

			�������TIM3CLKԤ��Ƶ����ô�����ܵõ�100Hz��Ƶ��
			�������÷�Ƶ�� = 1000�� ��ô  TIM3 counter clock = 72KHz
			TIM_Period = 720 - 1;
			Ƶ���²�����
		 */
		TIM_TimeBaseStructure.TIM_Period = 720 - 1;	/* TIM_Period = TIM3 ARR Register */
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

		/* PWM1 Mode configuration */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;// ���ģʽ
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	}	

	/*
		_bright = 1 ʱ, TIM_Pulse = 1
		_bright = 255 ʱ, TIM_Pulse = TIM_Period
	*/
	

	
	if(PWM_PB8_CH3 == PWM_CH)
	{
		TIM_OCInitStructure.TIM_Pulse = (TIM_TimeBaseStructure.TIM_Period * _bright) / BRIGHT_MAX;	/* �ı�ռ�ձ� */

		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	}
	
	if(PWM_PB9_CH4 == PWM_CH)
	{
		TIM_OCInitStructure.TIM_Pulse = (TIM_TimeBaseStructure.TIM_Period * _bright) / BRIGHT_MAX;	/* �ı�ռ�ձ� */

		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	}
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);

	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
}
