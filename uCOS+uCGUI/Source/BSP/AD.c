#include "includes.h"

u16 g_usAdcValue;	/* ADC ����ֵ��ƽ��ֵ */
u16 g_usAdc2Value;

/*
*********************************************************************************************************
*	�� �� ��: ADC_Configuration
*	����˵��: ����ADC, PC4ģʽ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void ADC_Configuration(unsigned int Channel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	__IO u16 ADCConvertedValue; //!< 

	if(Channel == ADC1_PC4_Channel1)
	{
		/* ʹ�� ADC1 and GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);

		/* ����PC4Ϊģ������(ADC Channel14) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* ����ADC1, ����DMA, ��������� */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);

		/* ����ADC1 ����ͨ��14 channel14 configuration */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
	}
	
	if(Channel == ADC1_PA2_Channel2)
	{
		/* ʹ�� ADC1 and GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

		/* ����PC4Ϊģ������(ADC Channel14) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* ����ADC1, ����DMA, ��������� */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);

		/* ����ADC1 ����ͨ��2 channel2 configuration */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);
	}
	
	if(Channel == ADC1_PA0_Channel0)
	{
		/* ʹ�� ADC1 and GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

		/* ����PA0Ϊģ������(ADC Channel0) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* ����ADC1, ����DMA, ��������� */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		
		ADC_Init(ADC1, &ADC_InitStructure);

		/* ����ADC1 ����ͨ��2 channel2 configuration */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	}
	
	/* ʹ��ADC1 DMA���� */
	ADC_DMACmd(ADC1, ENABLE);

	/* ʹ�� ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* ʹ��ADC1 ��λУ׼�Ĵ��� */
	ADC_ResetCalibration(ADC1);
	/* ���ADC1�ĸ�λ�Ĵ��� */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* ����ADC1У׼ */
	ADC_StartCalibration(ADC1);
	/* ���У׼�Ƿ���� */
	while(ADC_GetCalibrationStatus(ADC1));

	/* �������ADCת�� */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/*
*********************************************************************************************************
*	�� �� ��: ADC2_Configuration
*	����˵��: ����ADC, PC4ģʽ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void ADC2_Configuration(unsigned int Channel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	__IO u16 ADCConvertedValue; //!< 

	if(Channel == ADC2_PC4_Channel1)
	{
		/* ʹ�� ADC1 and GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOC, ENABLE);

		/* ����PC4Ϊģ������(ADC Channel14) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* ����ADC1, ����DMA, ��������� */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC2, &ADC_InitStructure);

		/* ����ADC1 ����ͨ��14 channel14 configuration */
		ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
	}
	
	if(Channel == ADC2_PA2_Channel2)
	{
		/* ʹ�� ADC1 and GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOA, ENABLE);

		/* ����PC4Ϊģ������(ADC Channel14) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* ����ADC1, ����DMA, ��������� */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC2, &ADC_InitStructure);

		/* ����ADC1 ����ͨ��2 channel2 configuration */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);
	}
	
	if(Channel == ADC2_PA0_Channel0)
	{
		/* ʹ�� ADC1 and GPIOC clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOA, ENABLE);

		/* ����PA0Ϊģ������(ADC Channel0) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* ����ADC1, ����DMA, ��������� */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		
		ADC_Init(ADC2, &ADC_InitStructure);

		/* ����ADC1 ����ͨ��2 channel2 configuration */
		ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	}
	
	/* ʹ��ADC1 DMA���� */
	ADC_DMACmd(ADC2, ENABLE);

	/* ʹ�� ADC1 */
	ADC_Cmd(ADC2, ENABLE);

	/* ʹ��ADC1 ��λУ׼�Ĵ��� */
	ADC_ResetCalibration(ADC2);
	/* ���ADC1�ĸ�λ�Ĵ��� */
	while(ADC_GetResetCalibrationStatus(ADC2));

	/* ����ADC1У׼ */
	ADC_StartCalibration(ADC2);
	/* ���У׼�Ƿ���� */
	while(ADC_GetCalibrationStatus(ADC2));

	/* �������ADCת�� */
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}





/*
*********************************************************************************************************
*	�� �� ��: GetADC
*	����˵��: ��ȡADC������ƽ��ֵ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AdcPro(void)
{
	static u16 buf[SAMP_COUNT];
	static u8 write;
	u32 sum;
	u8 i;
	
	
	{
		buf[write] = ADC_GetConversionValue(ADC1);
	}
	
	
	if (++write >= SAMP_COUNT)
	{
		write = 0;
	}

	/* 
		������δ��������ƽ��ֵ�ķ��������˲�
		Ҳ���Ը����£�ѡ��ȥ����������2��ֵ��ʹ���ݸ��Ӿ�ȷ
	*/
	sum = 0;
	for (i = 0; i < SAMP_COUNT; i++)
	{
		sum += buf[i];
	}
	g_usAdcValue = sum / SAMP_COUNT;	/* ADC����ֵ�����ɴβ���ֵƽ�� */

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	/* ��������´�ADCת�� */
}

/*
*********************************************************************************************************
*	�� �� ��: GetADC
*	����˵��: ��ȡADC������ƽ��ֵ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 u16 GetADC(void)
{
	u16 ret;
//	OS_CPU_SR  cpu_sr = 0;

	/* ��Ϊ	g_AdcValue ������systick�ж��и�д��
		 Ϊ�˱��������������ʱ���жϳ�����ҵ������ݴ��������Ҫ
		 �ر��жϽ��б��� 
	*/

	/* �����ٽ����������ر��ж� */
	//__set_PRIMASK(1);  /* ���ж� */
//	OS_ENTER_CRITICAL();

	ret = g_usAdcValue;
	
//	OS_EXIT_CRITICAL();

	//__set_PRIMASK(0);  /* ���ж� */

	return ret;
}

/*
*********************************************************************************************************
*	�� �� ��: ADC2Pro
*	����˵��: ��ȡADC������ƽ��ֵ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Adc2Pro(void)
{
	static u16 buf[SAMP_COUNT];
	static u8 write;
	u32 sum;
	u8 i;
	

	{
		buf[write] = ADC_GetConversionValue(ADC2);
	}
	
	if (++write >= SAMP_COUNT)
	{
		write = 0;
	}

	/* 
		������δ��������ƽ��ֵ�ķ��������˲�
		Ҳ���Ը����£�ѡ��ȥ����������2��ֵ��ʹ���ݸ��Ӿ�ȷ
	*/
	sum = 0;
	for (i = 0; i < SAMP_COUNT; i++)
	{
		sum += buf[i];
	}
	g_usAdc2Value = sum / SAMP_COUNT;	/* ADC����ֵ�����ɴβ���ֵƽ�� */

	ADC_SoftwareStartConvCmd(ADC2, ENABLE);	/* ��������´�ADCת�� */
}

/*
*********************************************************************************************************
*	�� �� ��: GetADC
*	����˵��: ��ȡADC������ƽ��ֵ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 u16 GetADC2(void)
{
	u16 ret;
//	OS_CPU_SR  cpu_sr = 0;


	/* �����ٽ����������ر��ж� */
	//__set_PRIMASK(1);  /* ���ж� */
	//OS_ENTER_CRITICAL();

	ret = g_usAdc2Value;
	
	//OS_EXIT_CRITICAL();

	//__set_PRIMASK(0);  /* ���ж� */

	return ret;
}


