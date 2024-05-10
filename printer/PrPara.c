#include <string.h>
#include "PrInput.h"
#include "PrPara.h"


static CPrPara	s_tPrPara = {
	0, PR_WIDTH_BITS,
	PRD_LINE_SPACE, 0, PRSV_JUST_LEFT,
	0,
};


int Pr_InitPara(void)
{
	s_tPrPara.vTextLeft = 0;
	s_tPrPara.vTextRegion = PR_WIDTH_BITS;
	s_tPrPara.vLineSpace = PRD_LINE_SPACE;
	s_tPrPara.vUnderline = 0;
	s_tPrPara.vJustification = PRSV_JUST_LEFT;
	s_tPrPara.vReverse = 0;

	return 0;
}

int Pr_ReadPara(CPrPara *ptPara)
{
	memcpy(ptPara, &s_tPrPara, sizeof(CPrPara));

	return 0;
}

int Pr_WritePara(CPrPara *ptPara)
{
	memcpy(&s_tPrPara, ptPara, sizeof(CPrPara));

	return 0;
}

unsigned int Pr_GetPara(int vType)
{
	int vRet = 0;

	switch(vType)
	{
	case PRS_TEXT_LEFT:
		vRet = s_tPrPara.vTextLeft;
		break;
	case PRS_TEXT_REGION:
		vRet = s_tPrPara.vTextRegion;
		break;
	case PRS_LINE_SPACE:
		vRet = s_tPrPara.vLineSpace;
		break;
	case PRS_UNDERLINE:
		vRet = s_tPrPara.vUnderline;
		break;
	case PRS_JUSTIFICATION:
		vRet = s_tPrPara.vJustification;
		break;

	case PRS_REVERSE:
		vRet = s_tPrPara.vReverse;
		break;

	default:
		break;
	}

	return vRet;
}

unsigned int Pr_SetPara(int vType, int vValue)
{
	int vRet = 0;

	switch(vType)
	{
	case PRS_TEXT_LEFT:
		vRet = s_tPrPara.vTextLeft;
		s_tPrPara.vTextLeft = vValue;
		break;
	case PRS_TEXT_REGION:
		vRet = s_tPrPara.vTextRegion;
		s_tPrPara.vTextRegion = vValue;
		break;
	case PRS_LINE_SPACE:
		vRet = s_tPrPara.vLineSpace;
		s_tPrPara.vLineSpace = vValue;
		break;
	case PRS_UNDERLINE:
		vRet = s_tPrPara.vUnderline;
		s_tPrPara.vUnderline = vValue;
		break;
	case PRS_JUSTIFICATION:
		vRet = s_tPrPara.vJustification;
		s_tPrPara.vJustification = vValue;
		break;

	case PRS_REVERSE:
		vRet = s_tPrPara.vReverse;
		s_tPrPara.vReverse = vValue;
		break;

	default:
		break;
	}

	return vRet;
}

