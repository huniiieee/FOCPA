#include "Analysis.h"

int main()
{
	char			FOLD_MERGE[_FILE_NAME_SIZE_] = "";
	char			FILE_MERGE[_FILE_NAME_SIZE_] = "";
	byte			W0[16] = { 0xc6,0x56,0x4c,0x72,0xfd,0x09,0x0e,0x85,0xab,0x24,0x0d,0xd7,0xe6,0x73,0x6f,0xf6 };
	byte			W1[16] = { 0x5b,0xf2,0x16,0x5a,0x49,0xd1,0x6c,0x56,0x28,0xdc,0xa1,0x29,0x6c,0x5c,0x19,0xa3 };
	FILE* fpp = NULL;
	FILE* fpt = NULL;

	unsigned int POINTS = 0;
	unsigned int TRACE_NUM = 0;

	// 평문 파일 열기 (읽기 모드)
	sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%s.txt", Folder_Path, Plain_Path);
	fopen_s(&fpp, FILE_MERGE, "r");
	if (fpp == NULL) {
		printf(" -----------------------------------------------------------------------\n");
		printf("|                        Failed To Read Plaintext                       |\n");
		printf(" -----------------------------------------------------------------------\n");
		return _FAIL_;
	}

	// 파형 파일 열기 (읽기 모드)
	sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%s.trace", Folder_Path, Trace_Path);
	fopen_s(&fpt, FILE_MERGE, "rb");
	if (fpt == NULL) {
		printf(" -----------------------------------------------------------------------\n");
		printf("|                          Failed To Read Trace                         |\n");
		printf(" -----------------------------------------------------------------------\n");
		return _FAIL_;
	}

	//ARIA
	// 
	//Point_Verify(&POINTS, &TRACE_NUM);
	//First_Order_CPA_ARIA(fpp,fpt,POINTS);
	//Find_Aria_Key(W0, W1);


	//PIPO_TLU & BS
	// 
	Point_Verify(&POINTS, &TRACE_NUM);
	//First_Order_CPA_PIPO_TLU(fpp,fpt,POINTS);
	First_Order_CPA_PIPO_BS(fpp,fpt,POINTS);
	fclose(fpp);
	fclose(fpt);
	return 0;
}