#ifndef _PR_INPUT_H
#define _PR_INPUT_H


// 打印宽度
#define PR_WIDTH_BITS		(384)
// 打印宽度对应的字节大小
#define PR_WIDTH_BYTES		(PR_WIDTH_BITS/8)


int Printer_Open(void);
int Printer_Close(void);
int Printer_Write(int vHeight, unsigned char *szBuf);


#endif
