#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MonoPix.h"


// 单位是比特
int MP_GetRealWidth(CMonoPix *ptPix)
{
	int vRealWidth;

	if(ptPix->vAlign == 0){
		vRealWidth = ptPix->vWidth;
	}
	else{
		vRealWidth = (ptPix->vWidth+7)/8*8;
	}

	return vRealWidth;
}

int MP_GetBufSize(CMonoPix *ptPix)
{
	int vSize;

	if(ptPix->vAlign == 0){
		// 仅缓存的最后字节对齐
		vSize = (ptPix->vWidth*ptPix->vHeight+7)/8;
	}
	else{
		// 每点行都字节对齐
		vSize = (ptPix->vWidth+7)/8*ptPix->vHeight;
	}

	return vSize;
}

CMonoPix MP_New(int vWidth, int vHeight, int vAlign, int vAlloc, unsigned char *szBuf)
{
	CMonoPix tPix;
    int vSize;

	memset(&tPix, 0, sizeof(CMonoPix));
	// 记录信息
	tPix.vWidth = vWidth;
	tPix.vHeight = vHeight;
	tPix.vAlign = vAlign;
	tPix.vAlloc = vAlloc;
	tPix.szPixBuf = szBuf;
	vSize = MP_GetBufSize(&tPix);
	// 申请缓存
	if(vAlloc == 0){
		tPix.szPixBuf = malloc(vSize);
		if(tPix.szPixBuf == NULL){
			goto LB_END;
		}
	}
	memset(tPix.szPixBuf, 0, vSize);

LB_END:
	return tPix;
}

int MP_Delete(CMonoPix *ptPix)
{
	// 释放空间
	if((ptPix->szPixBuf != NULL) && (ptPix->vAlloc == 0)){
		free(ptPix->szPixBuf);
	}
	// 清结构
	memset(ptPix, 0, sizeof(CMonoPix));

	return 0;
}

int MP_Valid(CMonoPix *ptPix)
{
	int vRet = 0;

	if((ptPix->vWidth == 0) || (ptPix->vHeight == 0)){
		vRet = -1;
		goto LB_END;
	}
	if((ptPix->vAlloc == 0) && (ptPix->szPixBuf == NULL)){
		vRet = -1;
		goto LB_END;
	}

LB_END:
	return vRet;
}

int MP_SetAll(CMonoPix *ptPix, int vValue)
{
	int vSize;

	vSize = MP_GetBufSize(ptPix);
	if(vValue == 0){
		memset(ptPix->szPixBuf, 0, vSize);
	}
	else{
		memset(ptPix->szPixBuf, 0xff, vSize);
	}

	return 0;
}

int MP_GetPoint(CMonoPix *ptPix, int vX, int vY)
{
	int vRet;
	int vRealW;
	int vIndByte, vIndBit;
	int vOffset;

	vRealW = MP_GetRealWidth(ptPix);
	vOffset = vRealW*vY+vX;
	vIndByte = vOffset/8;
	vIndBit = vOffset%8;
	vRet = ptPix->szPixBuf[vIndByte] & (0x80>>vIndBit);
	if(vRet != 0){
		vRet = 1;
	}

	return vRet;
}

int MP_SetPoint(CMonoPix *ptPix, int vX, int vY, int vValue)
{
	int vRealW;
	int vIndByte, vIndBit;
	int vOffset;
	int vMask;

	vRealW = MP_GetRealWidth(ptPix);
	vOffset = vRealW*vY+vX;
	vIndByte = vOffset/8;
	vIndBit = vOffset%8;
	vMask = 0x80>>vIndBit;
	if(vValue == 0){
		ptPix->szPixBuf[vIndByte] &= (~vMask);
	}
	else{
		ptPix->szPixBuf[vIndByte] |= vMask;
	}

	return 0;
}

int MP_Read(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY)
{
	int vFromX, vFromY;
	int vToX, vToY;
	int vBitVal;

	for(vToY=0; vToY<ptToPix->vHeight; vToY++){
		for(vToX=0; vToX<ptToPix->vWidth; vToX++){
			// 读取
			vFromX = vX+vToX;
			vFromY = vY+vToY;
			vBitVal = MP_GetPoint(ptFromPix, vFromX, vFromY);
			// 设置
			MP_SetPoint(ptToPix, vToX, vToY, vBitVal);
		}
	}

	return 0;
}

int MP_Write(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY)
{
	int vFromX, vFromY;
	int vToX, vToY;
	int vBitVal;

	for(vFromY=0; vFromY<ptFromPix->vHeight; vFromY++){
		for(vFromX=0; vFromX<ptFromPix->vWidth; vFromX++){
			// 读取
			vBitVal = MP_GetPoint(ptFromPix, vFromX, vFromY);
			// 设置
			vToX = vX+vFromX;
			vToY = vY+vFromY;
			MP_SetPoint(ptToPix, vToX, vToY, vBitVal);
		}
	}

	return 0;
}

int MP_Double(CMonoPix *ptOrgPix, CMonoPix *ptDblPix, int vX, int vY)
{
	int vOrgX, vOrgY;
	int vDblX, vDblY;
	int vBitVal;

	for(vOrgY=0, vDblY=vY; vOrgY<ptOrgPix->vHeight; vOrgY++, vDblY+=2){
		for(vOrgX=0, vDblX=vX; vOrgX<ptOrgPix->vWidth; vOrgX++, vDblX+=2){
			vBitVal = MP_GetPoint(ptOrgPix, vOrgX, vOrgY);
			MP_SetPoint(ptDblPix, vDblX, vDblY, vBitVal);
			MP_SetPoint(ptDblPix, vDblX+1, vDblY, vBitVal);
			MP_SetPoint(ptDblPix, vDblX, vDblY+1, vBitVal);
			MP_SetPoint(ptDblPix, vDblX+1, vDblY+1, vBitVal);
		}
	}

	return 0;
}

int MP_ShiftRight(CMonoPix *ptPix, int vBitCnt)
{
	int vFromX, vToX;
	int vY;
	int vBitVal;

	for(vY=0; vY<ptPix->vHeight; vY++){
		// 移位
		vFromX = ptPix->vWidth-1-vBitCnt;
		vToX = ptPix->vWidth-1;
		for(; vFromX>=0; vFromX--, vToX--){
			// 读取
			vBitVal = MP_GetPoint(ptPix, vFromX, vY);
			// 设置
			MP_SetPoint(ptPix, vToX, vY, vBitVal);
		}

	}
	// 填充
	for(vY=0; vY<ptPix->vHeight; vY++){
		for(vFromX=0; vFromX<vBitCnt; vFromX++){
			MP_SetPoint(ptPix, vFromX, vY, 0);
		}
	}

	return 0;
}

int MP_Reverse(CMonoPix *ptPix)
{
	int vSize;
	int vValue;
	int vIndex;

	vSize = MP_GetBufSize(ptPix);
	for(vIndex=0; vIndex<vSize; vIndex++){
		// 读取
		vValue = ptPix->szPixBuf[vIndex];
		// 设置
		ptPix->szPixBuf[vIndex] = ~vValue;
	}

	return 0;
}

int MP_Merge(CMonoPix *ptFromPix, CMonoPix *ptToPix)
{
	int vX, vY;
	int vRealF, vRealT;
	unsigned char vValue;
	int vIndexF, vIndexT;
	int vRealH, vRealW;

	vRealF = MP_GetRealWidth(ptFromPix)/8;
	vRealT = MP_GetRealWidth(ptToPix)/8;
	vRealW = vRealF > vRealT ? vRealT : vRealF;
	vRealH = ptToPix->vHeight > ptFromPix->vHeight ? ptFromPix->vHeight : ptToPix->vHeight;
	for(vY=0; vY<vRealH; vY++){
		for(vX=0; vX<vRealW; vX++){
			vIndexF = vY*vRealF+vX;
			vIndexT = vY*vRealT+vX;
			// 读取
			vValue = ptFromPix->szPixBuf[vIndexF];
			// 合并
			ptToPix->szPixBuf[vIndexT] |= vValue;
		}
	}

	return 0;
}

