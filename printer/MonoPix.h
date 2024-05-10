#ifndef _MONO_PIX_H
#define _MONO_PIX_H


typedef struct
{
	unsigned char	*szPixBuf;
	// ���䳤��bits
	int				vWidth;
	int				vHeight;
	// ���룺0--�������У�1--���ֽڶ���
	int				vAlign;
	// ���䣺0--ģ����䣻1--�ⲿ����
	int				vAlloc;
}CMonoPix;

// ��ȡ�����ӿ�
int MP_GetRealWidth(CMonoPix *ptPix);
int MP_GetBufSize(CMonoPix *ptPix);
// �����ӿ�
CMonoPix MP_New(int vWidth, int vHeight, int vAlign, int vAlloc, unsigned char *szBuf);
int MP_Delete(CMonoPix *ptPix);
int MP_Valid(CMonoPix *ptPix);

int MP_SetAll(CMonoPix *ptPix, int vValue);
int MP_GetPoint(CMonoPix *ptPix, int vX, int vY);
int MP_SetPoint(CMonoPix *ptPix, int vX, int vY, int vValue);
int MP_Read(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY);
int MP_Write(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY);
// ��չ�ӿ�
int MP_Double(CMonoPix *ptFromPix, CMonoPix *ptToPix, int vX, int vY);
int MP_ShiftRight(CMonoPix *ptPix, int vBitCnt);
int MP_Reverse(CMonoPix *ptPix);
int MP_Merge(CMonoPix *ptFromPix, CMonoPix *ptToPix);


#endif
