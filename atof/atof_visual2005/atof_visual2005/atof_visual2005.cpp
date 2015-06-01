// atof_visual2005.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>


// ------------------------------------------------------------------------- 
// ����       : StrToFloatA 
// ����       : ��һ���ַ���ת��Ϊ������ 
// ����ֵ  : float  
// ����       : char* pstrfloat 
// ��ע       :  
// ------------------------------------------------------------------------- 
float StrToFloat(char* pstrfloat) 
{ 
	// check 
	if (!pstrfloat) 
	{ 
		return 0.0; 
	} 

	bool bNegative = false; 
	bool bDec = false; 

	char* pSor = 0; 
	char chByte = '0'; 
	float fInteger = 0.0; 
	float fDecimal = 0.0; 
	float fDecPower = 0.1f; 

	// ������λ�жϣ��ж��Ƿ��Ǹ��� 
	if (pstrfloat[0] == '-') 
	{ 
		bNegative = true; 
		pSor = pstrfloat + 1; 
	} 
	else 
	{ 
		bNegative = false; 
		pSor = pstrfloat; 
	} 

	while (*pSor != '\0') 
	{ 
		chByte = *pSor; 

		if (bDec) 
		{ 
			// С�� 
			if (chByte >= '0' && chByte <= '9') 
			{ 
				fDecimal += (chByte - '0') * fDecPower; 
				fDecPower = fDecPower * 0.1; 
			} 
			else 
			{ 
				return (bNegative? -(fInteger +  fDecimal): fInteger + fDecimal); 
			} 
		} 
		else 
		{ 
			// ���� 
			if (chByte >= '0' && chByte <= '9') 
			{ 
				fInteger = fInteger * 10.0 + chByte - '0'; 
			} 
			else if (chByte == '.') 
			{ 
				bDec = true; 
			} 
			else 
			{ 
				return (bNegative? -fInteger : fInteger); 
			} 
		} 

		pSor++; 
	} 

	return (bNegative? -(fInteger +  fDecimal): fInteger + fDecimal); 
} 


int _tmain(int argc, _TCHAR* argv[])
{
	//_TCHAR FL[] = "3.141592656";
	printf("Hello\n\r");
	printf("StrToFloat(1.23569) = %f\n\n\t", StrToFloat("3.1415926"));
	return 0;
}

