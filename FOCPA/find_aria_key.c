#include "Analysis.h"
#include "Aria_Sbox_Table.h"
//4개의 W1후보를 구하는 함수
void Find_Aria_Key(byte* W0, byte* W1)
{
	byte state[16] = { 0, };
	byte tmp[16] = { 0, };
	byte state_128[128] = { 0, };
	
	byte guess1_128[128] = { 0, };
	byte guess2_128[128] = { 0, };
	byte guess3_128[128] = { 0, };
	byte guess4_128[128] = { 0, };

	byte guess1[16] = { 0, };
	byte guess2[16] = { 0, };
	byte guess3[16] = { 0, };
	byte guess4[16] = { 0, };

	byte zero[16] = { 0, };

	unsigned int start = 0;
	//state는 W1 >>> 19 ^ W1 <<<31
	//W1 <<<31 == W1 >>> 97
	//state는 W1 >>> 19 ^ W1 >>> 97
	for (int i = 0; i < 16; i++)
		state[i] = W0[i] ^ W1[i];

	memcpy(tmp, state, 16);

	//state <<< 19 == W1 ^ W1 >>>78
	for (int i = 0; i < 16; i++)
		state[i] = (byte)((tmp[(i + 2) % 16] << 3)) | (byte)(((tmp[(i + 2 + 1) % 16] >> (8 - 3))));

	//state_128은 state를 한 비트씩 배열로 나타낸 것
	for (int i = 0; i < 128; i++)
		state_128[i] = (state[i / 8] >> (7 - (i % 8))) & 0x1;

	//첫 비트 0 마지막 비트 0으로 추측
	guess1_128[0] = 0;
	guess1_128[127] = 0;
	start = 0;
	for (int i = 0; i < 63; i++)
	{
		guess1_128[(start - 78) % 128] = guess1_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}
	start = 127;
	for (int i = 0; i < 63; i++)
	{
		guess1_128[(start - 78) % 128] = guess1_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}

	//첫 비트 0 마지막 비트 1로 추측
	guess2_128[0] = 0;
	guess2_128[127] = 1;
	start = 0;
	for (int i = 0; i < 63; i++)
	{
		guess2_128[(start - 78) % 128] = guess2_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}
	start = 127;
	for (int i = 0; i < 63; i++)
	{
		guess2_128[(start - 78) % 128] = guess2_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}

	//첫 비트 1 마지막 비트 0로 추측
	guess3_128[0] = 1;
	guess3_128[127] = 0;
	start = 0;
	for (int i = 0; i < 63; i++)
	{
		guess3_128[(start - 78) % 128] = guess3_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}
	start = 127;
	for (int i = 0; i < 63; i++)
	{
		guess3_128[(start - 78) % 128] = guess3_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}

	//첫 비트 1 마지막 비트 1로 추측
	guess4_128[0] = 1;
	guess4_128[127] = 1;
	start = 0;
	for (int i = 0; i < 63; i++)
	{
		guess4_128[(start - 78) % 128] = guess4_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}
	start = 127;
	for (int i = 0; i < 63; i++)
	{
		guess4_128[(start - 78) % 128] = guess4_128[start] ^ state_128[start];
		start = (start - 78) % 128;
	}

	//W1 후보 4개
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
			guess1[i] += guess1_128[i * 8 + j] << (7 - j);
		printf("%02x", guess1[i]);
	}
	printf("\n");

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
			guess2[i] += guess2_128[i * 8 + j] << (7 - j);
		printf("%02x", guess2[i]);
	}
	printf("\n");

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
			guess3[i] += guess3_128[i * 8 + j] << (7 - j);
		printf("%02x", guess3[i]);
	}
	printf("\n");

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
			guess4[i] += guess4_128[i * 8 + j] << (7 - j);
		printf("%02x", guess4[i]);
	}
	printf("\n");

	//W1후보로 부터 키 후보 뽑기
	//후보 1
	memcpy(tmp, zero, 16);
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
			tmp[i] ^= Involution[i][j] * guess1[j];
	}
	memcpy(guess1, tmp, 16);

	guess1[0] = Inv_S1[guess1[0]];
	guess1[1] = Inv_S2[guess1[1]];
	guess1[2] = S1[guess1[2]];
	guess1[3] = S2[guess1[3]];
	
	guess1[4] = Inv_S1[guess1[4]];
	guess1[5] = Inv_S2[guess1[5]];
	guess1[6] = S1[guess1[6]];
	guess1[7] = S2[guess1[7]];
	
	guess1[8] = Inv_S1[guess1[8]];
	guess1[9] = Inv_S2[guess1[9]];
	guess1[10] = S1[guess1[10]];
	guess1[11] = S2[guess1[11]];

	guess1[12] = Inv_S1[guess1[12]];
	guess1[13] = Inv_S2[guess1[13]];
	guess1[14] = S1[guess1[14]];
	guess1[15] = S2[guess1[15]];

	for (int i = 0; i < 16; i++)
		guess1[i] = guess1[i] ^ C1[i];

	//후보 2
	memcpy(tmp, zero, 16);
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
			tmp[i] ^= Involution[i][j] * guess2[j];
	}
	memcpy(guess2, tmp, 16);

	guess2[0] = Inv_S1[guess2[0]];
	guess2[1] = Inv_S2[guess2[1]];
	guess2[2] = S1[guess2[2]];
	guess2[3] = S2[guess2[3]];

	guess2[4] = Inv_S1[guess2[4]];
	guess2[5] = Inv_S2[guess2[5]];
	guess2[6] = S1[guess2[6]];
	guess2[7] = S2[guess2[7]];

	guess2[8] = Inv_S1[guess2[8]];
	guess2[9] = Inv_S2[guess2[9]];
	guess2[10] = S1[guess2[10]];
	guess2[11] = S2[guess2[11]];

	guess2[12] = Inv_S1[guess2[12]];
	guess2[13] = Inv_S2[guess2[13]];
	guess2[14] = S1[guess2[14]];
	guess2[15] = S2[guess2[15]];

	for (int i = 0; i < 16; i++)
		guess2[i] = guess2[i] ^ C1[i];

	//후보3
	memcpy(tmp, zero, 16);
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
			tmp[i] ^= Involution[i][j] * guess3[j];
	}
	memcpy(guess3, tmp, 16);

	guess3[0] = Inv_S1[guess3[0]];
	guess3[1] = Inv_S2[guess3[1]];
	guess3[2] = S1[guess3[2]];
	guess3[3] = S2[guess3[3]];
		 
	guess3[4] = Inv_S1[guess3[4]];
	guess3[5] = Inv_S2[guess3[5]];
	guess3[6] = S1[guess3[6]];
	guess3[7] = S2[guess3[7]];
		 
	guess3[8] = Inv_S1[guess3[8]];
	guess3[9] = Inv_S2[guess3[9]];
	guess3[10] = S1[guess3[10]];
	guess3[11] = S2[guess3[11]];
		 
	guess3[12] = Inv_S1[guess3[12]];
	guess3[13] = Inv_S2[guess3[13]];
	guess3[14] = S1[guess3[14]];
	guess3[15] = S2[guess3[15]];

	for (int i = 0; i < 16; i++)
		guess3[i] = guess3[i] ^ C1[i];

	//후보4
	memcpy(tmp, zero, 16);
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
			tmp[i] ^= Involution[i][j] * guess4[j];
	}
	memcpy(guess4, tmp, 16);

	guess4[0] = Inv_S1[guess4[0]];
	guess4[1] = Inv_S2[guess4[1]];
	guess4[2] = S1[guess4[2]];
	guess4[3] = S2[guess4[3]];
		 
	guess4[4] = Inv_S1[guess4[4]];
	guess4[5] = Inv_S2[guess4[5]];
	guess4[6] = S1[guess4[6]];
	guess4[7] = S2[guess4[7]];
		 
	guess4[8] = Inv_S1[guess4[8]];
	guess4[9] = Inv_S2[guess4[9]];
	guess4[10] = S1[guess4[10]];
	guess4[11] = S2[guess4[11]];
		 
	guess4[12] = Inv_S1[guess4[12]];
	guess4[13] = Inv_S2[guess4[13]];
	guess4[14] = S1[guess4[14]];
	guess4[15] = S2[guess4[15]];

	for (int i = 0; i < 16; i++)
		guess4[i] = guess4[i] ^ C1[i];

	printf("최종후보키 4개\n");

	for (int i = 0; i < 16; i++)
		printf("%02x ", guess1[i]);
	printf("\n");

	for (int i = 0; i < 16; i++)
		printf("%02x ", guess2[i]);
	printf("\n");

	for (int i = 0; i < 16; i++)
		printf("%02x ", guess3[i]);
	printf("\n");

	for (int i = 0; i < 16; i++)
		printf("%02x ", guess4[i]);
	printf("\n");
}
