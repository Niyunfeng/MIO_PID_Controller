#ifndef __PID_H
#define __PID_H
typedef struct PID {
	float SetPoint;    // �趨Ŀ��Desired value
	float Proportion; // ��������Proportional Const
	float Integral;   // ���ֳ���Integral Const
	float Derivative; // ΢�ֳ���Derivative Const
	float LastError;  // Error[-1]	
	float PrevError;  // Error[-2]
	float SumError;   // Sums of Errors
}PID;
		  
u16 PIDCalc(u16 value_set,u16 value_measurement,unsigned int M);


#endif
