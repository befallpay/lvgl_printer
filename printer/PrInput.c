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
	// 如果空间已经分配，就直接退出
	if(s_tPrSim.szData == NULL){
		s_tPrSim.vIndexY = 0;
		s_tPrSim.szData = malloc(1*PR_WIDTH_BYTES);
	}

	return 0;
}

int Printer_Close(void)
{
	// 可以在此处释放空间
	// 或者不释放，累积所有打印数据
	return 0;
}

// 每次打印都重新分配内存
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
	// 写入模拟打印纸
	Bmp1_ToFile(PRS_PAPER_BMP, PR_WIDTH_BITS, s_tPrSim.vIndexY, s_tPrSim.szData);

LB_END:
	return vRet;
}


