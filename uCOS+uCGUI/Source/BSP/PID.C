#include "includes.h"

/*====================================================================================================
PID Function
The PID (���������֡�΢��) function is used in mainly
control applications. PIDCalc performs one iteration of the PID
algorithm.
While the PID function works, main is just a dummy program showing
a typical usage.
=====================================================================================================*/

/*====================================================================================================/
PID���㲿��
typedef struct PID {
	float SetPoint;    // �趨Ŀ��Desired value
	float Proportion; // ��������Proportional Const
	float Integral;   // ���ֳ���Integral Const
	float Derivative; // ΢�ֳ���Derivative Const
	float LastError;  // Error[-1]	
	float PrevError;  // Error[-2]
	float SumError;   // Sums of Errors
}PID;
=====================================================================================================*/

PID   value_PID[6];
extern float E_Percent[2];
/*
*********************************************************************************************************
*                                    PID Calc RESPONSE TASK
*
* Description : This task monitors the AD and Get the AD Value
*
* Arguments   : M=[0 1 2 3 4 5 ]  
*
* Returns     : none
*********************************************************************************************************
*/
u16 PIDCalc(u16 value_set,u16 value_measurement,unsigned int M)
{
	u16 value_out; // PID Response (Output)
	float NextPoint; // PID Feedback (Input)
	float dError,Error;
	
	value_PID[M].SetPoint = (float)value_set; // �趨ֵ
	NextPoint = (float)value_measurement; // ����ֵ
	Error = value_PID[M].SetPoint - NextPoint; // ƫ��

	if(0 == M || 2 == M || 4 == M)
	{
		Error = Error * E_Percent[0];		
	}
	else 
	{
		Error = Error * E_Percent[1];
	}
	
	value_PID[M].SumError += Error; // ����
	dError = value_PID[M].LastError - value_PID[M].PrevError; // ��ǰ΢��
	value_PID[M].PrevError = value_PID[M].LastError;
	value_PID[M].LastError = Error;
	
	//!< �޷�
  {
		if(value_PID[M].SumError>150)  
		{
			value_PID[M].SumError=150;
		}
		if(value_PID[M].SumError<-150)	  
		{  
			value_PID[M].SumError=-150;
		}
	}
	
	//!< ���PID����
	{
	value_out = (u16)(value_PID[M].Proportion * Error + value_PID[M].Integral * value_PID[M].SumError 
							 + value_PID[M].Derivative * dError);
	}
	
	//!< �޷�  ��ΪPWM���Ϊ255 ��С��Ϊ0
	{
		if(value_out>=255)
		{
			value_out=255;
		}
		else
		{		
			 if(value_out<=0)
			 {
				 value_out=0; // �ɷ�ĳ�0? 
			 }
		}
	}

	return value_out;
}


