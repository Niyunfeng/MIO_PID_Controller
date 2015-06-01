#include "Timer3.h"
/*******************************************************************************
* Function Name  : None
* Description    : ��ʱ��3 PWM���ռ�ձ�ȫ�ֱ��� 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
unsigned int T3CH1_DC = 50 ;     // ��ʱ��3ͨ��1ռ�ձ� ȫ�ֱ���
unsigned int T3CH2_DC = 50 ;     // ��ʱ��3ͨ��2ռ�ձ� ȫ�ֱ���
unsigned int T3CH3_DC = 50 ;     // ��ʱ��3ͨ��3ռ�ձ� ȫ�ֱ���
unsigned int T3CH4_DC = 50 ;     // ��ʱ��3ͨ��4ռ�ձ� ȫ�ֱ���

/*******************************************************************************
* Function Name  : Timer3_GPIO_Configuration
* Description    : ���ö�ʱ��3 PWM������� 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure_TIMER3PWM_PORTA;
    GPIO_InitTypeDef GPIO_InitStructure_TIMER3PWM_PORTB;

    GPIO_InitStructure_TIMER3PWM_PORTA.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
      GPIO_InitStructure_TIMER3PWM_PORTA.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure_TIMER3PWM_PORTA.GPIO_Mode = GPIO_Mode_AF_PP;            
      GPIO_Init(GPIOA, &GPIO_InitStructure_TIMER3PWM_PORTA);  

    GPIO_InitStructure_TIMER3PWM_PORTB.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
      GPIO_InitStructure_TIMER3PWM_PORTB.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure_TIMER3PWM_PORTB.GPIO_Mode = GPIO_Mode_AF_PP;            
      GPIO_Init(GPIOB, &GPIO_InitStructure_TIMER3PWM_PORTB); 
}

/*******************************************************************************
* Function Name  : Timer3_BASE_Configuration              ע�����
* Description    : ���û�������                              �� TIM_Period ���5000 Ϊһ����Ҫ����
* Input          : None                                         ������� ��ʼ��PWM�ź� �� ����PWMռ�ձ� �����ﶼ�õ�
* Output         : None                                         ���Ҫ����PWM���Ƶ�ʣ��������ᵽ�����������ﶼҪ���ڣ�
* Return         : None                    
*******************************************************************************/
void Timer3_BASE_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_DeInit(TIM3);                                           //���½�Timer����Ϊȱʡֵ
    TIM_InternalClockConfig(TIM3);                              //�����ڲ�ʱ�Ӹ�TIM3�ṩʱ��Դ
    TIM_TimeBaseStructure.TIM_Prescaler = 720;                    
    //Ԥ��Ƶϵ��Ϊ72����������Ԥ��Ƶ����ʱTIMER��Ƶ��Ϊ1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;     //����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ü�����ģʽΪ���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period = 5000 - 1;                    
    //���ü��������С��ÿ��5000�����Ͳ���һ�������¼�����PWM�����Ƶ��Ϊ50Hz,Fre = 20ms
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);              //������Ӧ�õ�TIM3��
} 

/*******************************************************************************
* Function Name  : Timer3_PWN_Configuration
* Description    : ����PWM���� 
* Input          : Dutyfactor �� ռ�ձ�  ��0~100��
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_PWN_Configuration(void)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;               //PWM��ʽ  ��1,2

    /*************************** ͨ��1 ********************************/
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //PWM����ʹ��
    TIM_OCInitStructure.TIM_Pulse = (T3CH1_DC * 5000) / 100;        //д�Ƚ�ֵ(ռ�ձ�����)
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //����������λ�����ȸߵ�ƽ�����ȵ͵�ƽ
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 

    /*************************** ͨ��2 ********************************/
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = (T3CH2_DC * 5000) / 100;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /*************************** ͨ��3 ********************************/
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = (T3CH3_DC * 5000) / 100;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /*************************** ͨ��4 ********************************/
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = (T3CH4_DC * 5000) / 100;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3, ENABLE);                       
    TIM_Cmd(TIM3, ENABLE); 
}

/*******************************************************************************
* Function Name  : TIM3PWM_4Channel_Configuration
* Description    : ��ʼ����ʱ��3��4��ͨ����PWM�����ռ�ձȳ�ʼ��Ϊ50% 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3PWM_4Channel_Configuration(void)
{
    Timer3_GPIO_Configuration();
    Timer3_BASE_Configuration();
    Timer3_PWN_Configuration();
}

/*******************************************************************************
* Function Name  : Adjust_DutyCycle
* Description    : ��ʱ��3����4��ͨ����ռ�ձ� 
* Input          : CHx : ���ͨ��   DC : ���ڵ�������
* Output         : None
* Return         : None
*******************************************************************************/
void Adjust_TIM3DutyCycle(unsigned char CHx , unsigned int DC)
{
    switch(CHx)
    {
        case CH1 :
        {
            TIM_SetCompare1( TIM3,((DC*5000)/100) );
            break;
        }
        case CH2 :
        {
            TIM_SetCompare2( TIM3,((DC*5000)/100) );
            break;
        }
        case CH3 :
        {
            TIM_SetCompare3( TIM3,((DC*5000)/100) );
            break;
        }
        case CH4 :
        {
            TIM_SetCompare4( TIM3,((DC*5000)/100) );
            break;
        }
        default  :
        {break;}
    }
}