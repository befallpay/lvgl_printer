#ifndef _PR_PARA_H
#define _PR_PARA_H


// printer default
#define PRD_LINE_SPACE		(5)			// �м��
#define PRD_FONT_SIZE		(24)		// �����С

// for PRS_JUSTIFICATION
enum
{
	// ��lvgl����һ��
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
	unsigned int vTextLeft;		// �ı���߾�
	unsigned int vTextRegion;	// �ı�����
	unsigned int vLineSpace;	// �ı��м��
	unsigned int vUnderline;	// �ı��»���
	unsigned int vJustification;// �ı����뷽ʽ
	unsigned int vReverse;		// ����
}CPrPara;

int Pr_InitPara(void);
int Pr_ReadPara(CPrPara *ptPara);
int Pr_WritePara(CPrPara *ptPara);
unsigned int Pr_GetPara(int vType);
unsigned int Pr_SetPara(int vType, int vValue);

#endif

