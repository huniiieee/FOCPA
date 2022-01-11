#include "Analysis.h"


void Point_Verify(unsigned int* POINTS, unsigned int* TRACE_NUM)
{
	Trace_Header trace_header;
	FILE* fpp = NULL;
	FILE* fpt = NULL;

	char			FILE_MERGE[_FILE_NAME_SIZE_] = "";

	// ���� ���� ���� (�б� ���)
	sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%s.trace", Folder_Path, Trace_Path);
	fopen_s(&fpt, FILE_MERGE, "rb");
	if (fpt == NULL) {
		printf(" -----------------------------------------------------------------------\n");
		printf("|                          Failed To Read Trace                         |\n");
		printf(" -----------------------------------------------------------------------\n");
		return _FAIL_;
	}

	fread(trace_header.strID, sizeof(unsigned char), 20, fpt);
	fread(&trace_header.Point_No, sizeof(unsigned int), 1, fpt);
	fread(&trace_header.Trace_No, sizeof(unsigned int), 1, fpt);
	fread(trace_header.strEND, sizeof(unsigned char), 4, fpt);
	
	*POINTS = trace_header.Point_No;
	*TRACE_NUM = trace_header.Trace_No;
}
