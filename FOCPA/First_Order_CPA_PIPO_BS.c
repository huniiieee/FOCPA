#include "Analysis.h"
#include "Pipo_Sbox_Table.h"
void convert(byte* state)
{
	int i, j;
	byte T[8] = { 0, };
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			T[i] |= (((state[j] & (1 << (7 - i))) >> (7 - i)) << (7 - j));

	for (i = 0; i < 8; i++)
		state[i] = T[i];
}
void SLayer_TLU(byte* state)
{
	convert(state);
	state[0] = Pipo_SBox[state[0]];
	state[1] = Pipo_SBox[state[1]];
	state[2] = Pipo_SBox[state[2]];
	state[3] = Pipo_SBox[state[3]];
	state[4] = Pipo_SBox[state[4]];
	state[5] = Pipo_SBox[state[5]];
	state[6] = Pipo_SBox[state[6]];
	state[7] = Pipo_SBox[state[7]];
	convert(state);
}
void SLayer_BS(byte* state)
{
	byte T[3] = { 0, };
	state[2] ^= (state[0] & state[1]);
	state[3] ^= (state[4] & state[2]);
	state[0] ^= state[3];
	state[1] ^= state[4];
	state[4] ^= (state[3] | state[2]);
	state[2] ^= state[0];
	state[3] ^= (state[2] & state[1]);

	state[5] ^= state[6] & state[7];
	state[7] ^= state[5] | state[6];
	state[6] ^= state[5] | state[7];
	state[5] = ~state[5];

	// Extend XOR
	state[0] ^= state[6]; state[4] ^= state[5]; state[3] ^= state[7];

	//S5_2
	T[0] = state[0]; T[1] = state[4]; T[2] = state[3];
	state[1] ^= (T[0] & state[2]);
	T[0] ^= state[1];
	state[1] ^= (T[2] | T[1]);
	T[1] ^= state[2];
	state[2] ^= (state[1] | T[2]);
	T[2] ^= (T[1] & T[0]);
	// truncate XOR and swap
	state[5] ^= T[0]; T[0] = state[6] ^ T[2]; state[6] = state[7] ^ T[1];
	state[7] = state[0]; state[0] = T[0];
	T[1] = state[4]; state[4] = state[1]; state[1] = T[1];
	T[2] = state[3]; state[3] = state[2]; state[2] = T[2];

}

void First_Order_CPA_PIPO_BS(FILE* pt, FILE* trace, unsigned int Total_Point)
{
	__int64* HW_BYTES = NULL;
	__int64* HWW_BYTES = NULL;

	double* TR_POINTS = NULL;
	double* TRR_POINTS = NULL;
	double** HW_TR = NULL;
	double* Max = NULL;
	double* Temp_Points = NULL;

	HW_BYTES = (__int64*)malloc(Guess_Key_Num * sizeof(__int64));
	HWW_BYTES = (__int64*)malloc(Guess_Key_Num * sizeof(__int64));

	TR_POINTS = (double*)malloc((unsigned int)Point_Num * sizeof(double));
	TRR_POINTS = (double*)malloc((unsigned int)Point_Num * sizeof(double));
	Max = (double*)malloc(Guess_Key_Num * sizeof(double));
	Temp_Points = (double*)malloc((unsigned int)Point_Num * sizeof(double));

	HW_TR = (double**)malloc(Guess_Key_Num * sizeof(double*));
	for (unsigned int i = 0; i < Guess_Key_Num; i++)
		HW_TR[i] = (double*)malloc((unsigned int)Point_Num * sizeof(double));

	byte _pt_[8] = { 0, };
	byte T[8] = { 0, };
	byte Key[8] = { 0, };
	unsigned int hw = 0;

	float F_Temp;
	int mid = 0;
	double corr_m = 0.;
	double corr_d = 0.;
	double corr = 0.;
	double max_cor = 0.;
	double max_key = 0.;
	unsigned int key_can = 0;

	for (int _byte_ = Start_Byte - 1; _byte_ < 1; _byte_++)
	{
		//값 초기화

		for (unsigned int guess_key = Guess_Key_Start; guess_key < Guess_Key_End; guess_key++)
		{
			HW_BYTES[guess_key] = 0;
			HWW_BYTES[guess_key] = 0;
			Max[guess_key] = 0.0;
		}


		for (unsigned int point = 0; point < Point_Num; point++)
		{
			TR_POINTS[point] = 0.0;
			TRR_POINTS[point] = 0.0;
			for (unsigned int guess_key = Guess_Key_Start; guess_key < Guess_Key_End; guess_key++)
				HW_TR[guess_key][point] = 0.0;
		}



		_fseeki64(pt, (__int64)0, SEEK_SET);
		_fseeki64(trace, (__int64)32 + ((__int64)Start_Point - (__int64)1) * (__int64)4, SEEK_SET);

		for (__int64 _trace_ = 0; _trace_ < Trace_Num; _trace_++)
		{
			for (int i = 0; i < 8; i++)
				fscanf_s(pt, "%hhx", &_pt_[i]);
			_fseeki64(pt, (__int64)3 * 8 + (__int64)2, SEEK_CUR);

			for (__int64 point = 0; point < Point_Num; point++)
			{
				fread(&F_Temp, sizeof(float), 1, trace);
				Temp_Points[point] = (double)F_Temp;

				TR_POINTS[point] += Temp_Points[point];
				TRR_POINTS[point] += Temp_Points[point] * Temp_Points[point];
			}
			_fseeki64(trace, ((__int64)Total_Point - (__int64)End_Point + (__int64)Start_Point - (__int64)1) * (__int64)4, SEEK_CUR);

			convert(_pt_);
			for (__int64 guess_key = Guess_Key_Start; guess_key < Guess_Key_End; guess_key++)
			{
				mid=Pipo_SBox[_pt_[0] ^ guess_key];
				
				
				hw = (mid >> 4) & 1;
				
				
				//hw = (mid & 1) + ((mid >> 1) & 1) + ((mid >> 2) & 1) + ((mid >> 3) & 1) + ((mid >> 4) & 1) + ((mid >> 5) & 1) + ((mid >> 6) & 1) + ((mid >> 7) & 1);
				HW_BYTES[guess_key] += (__int64)hw;
				HWW_BYTES[guess_key] += (__int64)(hw * hw);
				for (__int64 point = 0; point < Point_Num; point++)
					HW_TR[guess_key][point] += (double)hw * Temp_Points[point];
			}
		}

		max_key = 0.0;
		for (__int64 guess_key = Guess_Key_Start; guess_key < Guess_Key_End; guess_key++)
		{
			max_cor = 0.0;
			for (__int64 point = 0; point < Point_Num; point++)
			{
				corr_m = (double)Trace_Num * HW_TR[guess_key][point] - (double)HW_BYTES[guess_key] * TR_POINTS[point];
				corr_d = ((double)Trace_Num * (double)HWW_BYTES[guess_key] - (double)HW_BYTES[guess_key] * (double)HW_BYTES[guess_key]) * ((double)Trace_Num * TRR_POINTS[point] - TR_POINTS[point] * TR_POINTS[point]);
				if (corr_d <= (double)0)
					corr = 0.0;
				else
				{
					corr = corr_m / sqrt(corr_d);
					corr = fabs(corr);
				}
				if (corr > max_cor)
				{
					max_cor = corr;
					Max[guess_key] = max_cor;
				}
			}
			if (Max[guess_key] > max_key)
			{
				max_key = Max[guess_key];
				key_can = guess_key;
			}

		}

		printf("%d번 째 byte의 후보키는 %04X이고, max_correlation=%f\n", _byte_, key_can, max_key);
		Max[key_can] = 0.0;
		for (int i = 0; i < 10; i++)
		{
			max_key = 0.0;
			for (int j = 0; j < Guess_Key_Num; j++)
			{
				if (Max[j] > max_key)
				{
					max_key = Max[j];
					key_can = j;
				}
			}
			printf("\n %d번째 후보 RK[23] ==>>>%08x %f\n", i + 1, key_can, max_key);
			Max[key_can] = 0.0;
		}
	}

	free(HW_BYTES);
	free(HWW_BYTES);
	free(TR_POINTS);
	free(TRR_POINTS);
	free(Max);
	free(Temp_Points);
	for (unsigned int i = 0; i < Guess_Key_Num; i++)
		free(HW_TR[i]);
	free(HW_TR);




}
