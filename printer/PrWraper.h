#ifndef _PR_WRAPER_H
#define _PR_WRAPER_H


int Pr_Open(void);
int Pr_Close(void);
int Pr_Write(int vHeight, void *szBuf);

int Pr_DotLines(int vLines);
int Pr_TextLines(int vLines);
int Pr_MonoData(unsigned int vWidth, unsigned int vHeight, unsigned char *szData);


#endif
