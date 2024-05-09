#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrEmu.h"
#include "PrInput.h"


#define PRS_PAPER_BMP			"paper.bmp"

typedef struct {
	unsigned char	*szData;
	int		vIndexY;
}CPrSim;
static CPrSim	s_tPrSim = {NULL, 0};

int Printer_Open(void)
{
	// ����ռ��Ѿ����䣬��ֱ���˳�
	if(s_tPrSim.szData == NULL){
		s_tPrSim.vIndexY = 0;
		s_tPrSim.szData = malloc(1*PR_WIDTH_BYTES);
	}

	return 0;
}

int Printer_Close(void)
{
	// �����ڴ˴��ͷſռ�
	// ���߲��ͷţ��ۻ����д�ӡ����
	return 0;
}

// ÿ�δ�ӡ�����·����ڴ�
int Printer_Write(int vHeight, unsigned char *szBuf)
{
	int vRet = 0;
	int vOldSize, vInSize, vNewSize;
	unsigned char *ptr = NULL;

	vOldSize = s_tPrSim.vIndexY*PR_WIDTH_BYTES;
	vInSize = PR_WIDTH_BYTES*vHeight;
	vNewSize = vOldSize+vInSize;
    ptr = realloc(s_tPrSim.szData, vNewSize);
    if(ptr == NULL){
		vRet = -1;
		goto LB_END;
	}

    memcpy(ptr+vOldSize, szBuf, vInSize);
    s_tPrSim.vIndexY += vHeight;
    s_tPrSim.szData = ptr;
	// д��ģ���ӡֽ
	Bmp1_ToFile(PRS_PAPER_BMP, PR_WIDTH_BITS, s_tPrSim.vIndexY, s_tPrSim.szData);

LB_END:
	return vRet;
}


