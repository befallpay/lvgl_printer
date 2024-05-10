#ifndef _PR_PARA_H
#define _PR_PARA_H


// printer default
#define PRD_LINE_SPACE		(5)			// 行间距
#define PRD_FONT_SIZE		(24)		// 字体大小

// for PRS_JUSTIFICATION
enum
{
	// 与lvgl保持一致
	PRSV_JUST_LEFT = 1,
	PRSV_JUST_MID,
	PRSV_JUST_RIGHT
};

// printer set
enum{
	PRS_TEXT_LEFT = 0,
	PRS_TEXT_REGION,
	PRS_LINE_SPACE,
	PRS_UNDERLINE,
	PRS_JUSTIFICATION,
	PRS_REVERSE,
};

typedef struct
{
	unsigned int vTextLeft;		// 文本左边距
	unsigned int vTextRegion;	// 文本区域
	unsigned int vLineSpace;	// 文本行间距
	unsigned int vUnderline;	// 文本下划线
	unsigned int vJustification;// 文本对齐方式
	unsigned int vReverse;		// 反显
}CPrPara;

int Pr_InitPara(void);
int Pr_ReadPara(CPrPara *ptPara);
int Pr_WritePara(CPrPara *ptPara);
unsigned int Pr_GetPara(int vType);
unsigned int Pr_SetPara(int vType, int vValue);

#endif

