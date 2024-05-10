#ifndef _MONO_PIX_H
#define _MONO_PIX_H


typedef struct
{
	unsigned char	*szPixBuf;
	// 分配长宽：bits
	int				vWidth;
	int				vHeight;
	// 对齐：0--紧凑排列；1--单字节对齐
	int				vAlign;
	// 分配：0--模块分配；1--外部传入
	int				vAlloc;
}CMonoPix;

// 获取参数接口
int MP_GetRealWidth(CMonoPix *ptPix);
int MP_GetBufSize(CMonoPix *ptPix);
// 基础接口
CMonoPix MP_New(int vWidth, int vHeight, int vAlign, int vAlloc, unsigned char *szBuf);
int MP_Delete(CMonoPix *ptPix);
int MP_Valid(CMonoPix *ptPix);

int MP_SetAll(CMonoPix *ptPix, int vValue);
int MP_GetPoint(CMonoPix *ptPix, int vX, int vY);
int MP_SetPoint(CMonoPix *ptPix, int vX, int vY, int vValue);
int MP_Read(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY);
int MP_Write(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY);
// 扩展接口
int MP_Double(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY);
int MP_ShiftRight(CMonoPix *ptPix, int vBitCnt);
int MP_Reverse(CMonoPix *ptPix);
int MP_Merge(CMonoPix *ptFromPix, CMonoPix *ptToPix);


#endif
