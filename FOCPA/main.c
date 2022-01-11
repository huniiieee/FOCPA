#include "Analysis.h"

int main()
{
	char			FOLD_MERGE[_FILE_NAME_SIZE_] = "";
	char			FILE_MERGE[_FILE_NAME_SIZE_] = "";
	FILE* fpp = NULL;
	FILE* fpt = NULL;

	unsigned int POINTS = 0;
	unsigned int TRACE_NUM = 0;

	// �� ���� ���� (�б� ���)
	sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%s.txt", Folder_Path, Plain_Path);
	fopen_s(&fpp, FILE_MERGE, "r");
	if (fpp == NULL) {
		printf(" -----------------------------------------------------------------------\n");
		printf("|                        Failed To Read Plaintext                       |\n");
		printf(" -----------------------------------------------------------------------\n");
		return _FAIL_;
	}

	// ���� ���� ���� (�б� ���)
	sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%s.trace", Folder_Path, Trace_Path);
	fopen_s(&fpt, FILE_MERGE, "rb");
	if (fpt == NULL) {
		printf(" -----------------------------------------------------------------------\n");
		printf("|                          Failed To Read Trace                         |\n");
		printf(" -----------------------------------------------------------------------\n");
		return _FAIL_;
	}

	Point_Verify(&POINTS, &TRACE_NUM);
	First_Order_CPA(fpp, fpt,POINTS);

	fclose(fpp);
	fclose(fpt);
	return 0;
}