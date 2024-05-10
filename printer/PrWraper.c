#include <stdlib.h>
#include <string.h>
#include "PrInput.h"
#include "PrPara.h"
#include "MonoPix.h"
#include "PrLvgl.h"
#include "PrWraper.h"


// RGB565 to mono
static unsigned int Pr_Clr2Mono(unsigned int vColor)
{
	unsigned int vR, vG, vB;
	unsigned int vGray;
	unsigned int vMono;

	vR = vColor>>11;
	vG = (vColor&0x7e0)>>5;
	vB = vColor&0x1f;
	vR = vR*256/32;
	vG = vG*256/64;
	vB = vB*256/32;
	vGray = (int) (((float)vR) * 0.299f + ((float)vG) * 0.587f + ((float)vB) * 0.114f);
	vMono = vGray >= 0x80 ? 0 : 1;

	return vMono;
}

int Pr_Open(void)
{
	int vRet;

	vRet = Printer_Open();

	return vRet;
}

int Pr_Close(void)
{
	int vRet;

	vRet = Printer_Close();

	return vRet;
}

int Pr_Write(int vHeight, void *szBuf)
{
	int vRet = 0;
	int vRes;
	int i, j;
	unsigned int vMono;
	CMonoPix tPix;
	unsigned short *szData = szBuf;

	tPix = MP_New(PR_WIDTH_BITS, vHeight, 1, 0, NULL);
	if(MP_Valid(&tPix) != 0){
		vRet = -1;
		goto LB_END;
	}

	for(i=0; i<vHeight; i++){
		for(j=0; j<PR_WIDTH_BITS; j++){
			vMono = Pr_Clr2Mono(szData[i*PR_WIDTH_BITS+j]);
			if(vMono != 0){
				MP_SetPoint(&tPix, j, i, 1);
			}
		}
	}

	vRes = Printer_Write(vHeight, tPix.szPixBuf);
	if(vRes != 0){
		vRet = -2;
		goto LB_END;
	}

LB_END:
	if(MP_Valid(&tPix) == 0){
		MP_Delete(&tPix);
	}
	return vRet;
}

int Pr_DotLines(int vLines)
{
	int vRet;
	CMonoPix tPix;

	tPix = MP_New(PR_WIDTH_BITS, vLines, 1, 0, NULL);
	vRet = Pr_Write(tPix.vHeight, tPix.szPixBuf);
	MP_Delete(&tPix);

	return vRet;
}

int Pr_TextLines(int vLines)
{
	int vRet = 0;
	int vRes;
	int vLen;
	char *strText = NULL;

	vLen = vLines+1;
	strText = malloc(vLen);
	if(strText == NULL){
		vRet = -1;
		goto LB_END;
	}
	memset(strText, '\n', vLines);
	vRes = Pr_Text(strText);
	if(vRes != 0){
		vRet = -2;
		goto LB_END;
	}

LB_END:
	if(strText != NULL){
		free(strText);
	}
	return vRet;
}

int Pr_MonoData(unsigned int vWidth, unsigned int vHeight, unsigned char *szData)
{
	int vRet = 0;
	int vJust, vShift;
	CMonoPix tPix = {0};

	// 有效性判断
	if((vWidth <= 0) || (vWidth > PR_WIDTH_BITS)){
		vRet = -1;
		goto LB_END;
	}

	// 缓存不存在，申请缓存
	tPix = MP_New(vWidth, vHeight, 1, 1, szData);
	// 对齐处理
	vJust = Pr_GetPara(PRS_JUSTIFICATION);
	vShift = PR_WIDTH_BITS - vWidth;
	if(vJust == PRSV_JUST_LEFT){
		vShift = 0;
	}
	else if(vJust == PRSV_JUST_MID){
		vShift >>= 1;
	}
	if(vShift != 0){
		MP_ShiftRight(&tPix, vShift);
	}
	// 打印
	vRet = Pr_Write(tPix.vHeight, tPix.szPixBuf);

LB_END:
	if(MP_Valid(&tPix) == 0){
		MP_Delete(&tPix);
	}
	return vRet;
}

