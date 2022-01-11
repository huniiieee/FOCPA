#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_


/*
* 분석 가능 바이트 수
*/
#define Byte_Num 16


/*
*분석할 파형과 평문이 위치한 폴더 경로
*파형 이름
*평문 이름
*/

#define Folder_Path "C:\\Users\\leesehun\\chipwhisperer\\projects\\tmp\\default_data\\traces"
#define Trace_Path "2021.12.30-16.41.01-2021.12.30-16.41.01_1000tr_9224pt"
#define Plain_Path "2021.12.30-16.41.01-2021.12.30-16.41.01_1000tr_9224pt_plain"

/*
* 중간값 설정
* 0: AddRoundkey 이후
* 1: SubBytes 이후
*/
#define Mid_Value 1


/*
* 분석 시작 바이트
* 분석 종료 바이트 
*/
#define Start_Byte 1
#define End_Byte 16

/*
* 분석할 파형 수 
* 분석 시작 포인트 수 
* 분석 종료 포인트 수
* 총 분석 포인트 수
*/
#define Trace_Num 1000
#define Start_Point 1
#define End_Point 9224
#define Point_Num 9224

/*
* 최종 후보키 개수
*/
#define Candidates 3

/*
* 키 추측 시작 키
* 키 추축 종료 키
*/
#define Guess_Key_Start 0
#define Guess_Key_End 256
#define Guess_Key_Num 256

/*
* 추측 키들의 상관계수 출력 유무
* 1: 출력 //  0: 미출력
*/
#define Correlation 1


/*
* 추측 키들의 최대 상관계수 출력 유무(분석 파형 수를 늘려가면서 분석)
* 1:출력 //  0: 미출력
*/
#define _MAX_PEAK_TRACE_			1


/*
* 증가하는 분석 파형 수 단위
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
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <direct.h>

#define _FILE_NAME_SIZE_	1000
#define _PASS_				1
#define _FAIL_				0

typedef uint8_t byte;
int Log(struct tm* TIME, __int64 START_TIME, __int64 END_TIME);
void Point_Verify(unsigned int* POINTS, unsigned int* TRACE_NUM);
void First_Order_CPA(FILE* pt, FILE* trace, unsigned int Total_Point);

#endif
