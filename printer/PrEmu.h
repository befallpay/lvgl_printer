#ifndef _PR_EMU_H
#define _PR_EMU_H


#pragma pack(1)

// �ļ�ͷ��ԭ��СΪ12: Ϊ������,��Ϣ���С�����˽ṹ
typedef struct
{
    unsigned char   szType[2];
    // bmp�ļ����ܴ�С
    unsigned int    vFileSize;
    // ����
    unsigned short  vReserve1;
    unsigned short  vReserve2;
    // �������ݵ�ƫ��
    unsigned int    vDataOffset;
    // ��Ϣ��Ĵ�С:��֧��12��40����
    unsigned int    vInfoSize;
}CBmpHead;

// ��Ϣͷ��ԭ��С40��Ϊ������,��ԱvInfoSize(��Ϣ���С)����HEAD
typedef struct
{
    int             vWidth;
    int             vHeight;
    unsigned short  vPlanes;
    unsigned short  vBitsPerPix;
    unsigned int    vCompression;
    unsigned int    vImageSize;
    unsigned int    vXPelsPerMeter;
    unsigned int    vYPelsPerMeter;
    unsigned int    vClrUsed;
    unsigned int    vClrImportant;
}CBmpMsg;

typedef struct
{
    unsigned char vRed;
    unsigned char vGreen;
    unsigned char vBlue;
    unsigned char vAlpha;
}CBmpPaleItem;

// ��ɫ�壺16λ
typedef struct
{
    unsigned int vRed;
    unsigned int vGreen;
    unsigned int vBlue;
    unsigned int vAlpha;
}CBmpPaleMask;

typedef struct
{
    CBmpHead		tHead;
	CBmpMsg			tMsg;
	CBmpPaleItem	taPale[2];
	unsigned char	szData[0];
}CBmp1;

typedef struct
{
    CBmpHead		tHead;
	CBmpMsg			tMsg;
	CBmpPaleMask	taPale[1];
	unsigned char	szData[0];
}CBmp16;

#pragma pack()


int Bmp1_ToFile(const char *strName, int vWidth, int vHeight, unsigned char *szData);


#endif
