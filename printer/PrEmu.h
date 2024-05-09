#ifndef _PR_EMU_H
#define _PR_EMU_H


#pragma pack(1)

// 文件头，原大小为12: 为方便编程,信息域大小移至此结构
typedef struct
{
    unsigned char   szType[2];
    // bmp文件的总大小
    unsigned int    vFileSize;
    // 保留
    unsigned short  vReserve1;
    unsigned short  vReserve2;
    // 像素数据的偏移
    unsigned int    vDataOffset;
    // 信息域的大小:仅支持12和40两种
    unsigned int    vInfoSize;
}CBmpHead;

// 信息头，原大小40：为方便编程,成员vInfoSize(信息域大小)移至HEAD
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

// 调色板：16位
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
