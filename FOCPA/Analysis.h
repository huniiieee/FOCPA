#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_


/*
* �м� ���� ����Ʈ ��
*/
#define Byte_Num 16


/*
*�м��� ������ ���� ��ġ�� ���� ���
*���� �̸�
*�� �̸�
*/

#define Folder_Path " "
#define Trace_Path " "
#define Plain_Path " "

/*
* �߰��� ����
* 0: AddRoundkey ����
* 1: SubBytes ����
*/
#define Mid_Value 0


/*
* �м� ���� ����Ʈ
* �м� ���� ����Ʈ 
*/
#define Start_Byte 1
#define End_Byte 16

/*
* �м��� ���� �� 
* �м� ���� ����Ʈ �� 
* �м� ���� ����Ʈ ��
*/
#define Trace_Num 100
#define Start_Point 100
#define End_Point 1000

/*
* ���� �ĺ�Ű ����
*/
#define Candidates

/*
* Ű ���� ���� Ű
* Ű ���� ���� Ű
*/
#define Guess_Key_Start 0
#define Guess_Key_End 256

/*
* ���� Ű���� ������ ��� ����
* 1: ��� //  0: �����
*/
#define Correlation 1


/*
* ���� Ű���� �ִ� ������ ��� ����(�м� ���� ���� �÷����鼭 �м�)
* 1:��� //  0: �����
*/
#define _MAX_PEAK_TRACE_			1


/*
* �����ϴ� �м� ���� �� ����
*/
#if _MAX_PEAK_TRACE_
#define _TRACE_UNIT_				10
#endif


typedef struct{
	unsigned char strID[20];
	unsigned int Trace_No;
	unsigned int Point_No;
	unsigned char strEND[4];
} Trace_Header;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <direct.h>

#define _FILE_NAME_SIZE_	1000
#define _PASS_				1
#define _FAIL_				0

int Log(struct tm* TIME, __int64 START_TIME, __int64 END_TIME);
int Point_Verify(unsigned int* POINTS, unsigned int* TRACE_NUM);
int First_Order_CPA(struct tm* TIME, unsigned int POINTS, unsigned int TRACE_NUM);

#endif
