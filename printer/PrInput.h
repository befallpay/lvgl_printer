#ifndef _PR_INPUT_H
#define _PR_INPUT_H


// ��ӡ���
#define PR_WIDTH_BITS		(384)
// ��ӡ��ȶ�Ӧ���ֽڴ�С
#define PR_WIDTH_BYTES		(PR_WIDTH_BITS/8)


int Printer_Open(void);
int Printer_Close(void);
int Printer_Write(int vHeight, unsigned char *szBuf);


#endif
