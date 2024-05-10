#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "PrConf.h"
#include "MonoPix.h"
#include "PrInput.h"
#include "PrPara.h"
#include "PrWraper.h"
#include "PrLvgl.h"
#include "PrCmd.h"


int Pr_IsCmdCode(const unsigned char *szText)
{
	int vRet = 0;

	if((*szText == PRC_ESC) || (*szText == PRC_GS)){
		vRet = 1;
	}

	return vRet;
}

int Pr_IsTextEnd(const unsigned char *szText)
{
	int vRet = 0;

	if(szText[0] == '\r'){
		vRet += 1;
		if(szText[1] == '\n'){
			vRet += 1;
		}
	}
	else if(szText[0] == '\n'){
		vRet += 1;
	}

	return vRet;
}

int Pr_EscDeal(const unsigned char *szContent)
{
	int vRet = 3;
	unsigned char vSubCmd, vPara;

	vSubCmd = szContent[1];
	vPara = szContent[2];
	switch(vSubCmd)
	{
	case ESC_UNDERLINE:
		Pr_SetPara(PRS_UNDERLINE, vPara);
		break;

	case ESC_LINE_SPACE:
		Pr_SetPara(PRS_LINE_SPACE, vPara);
		break;

	case ESC_INITIALIZE:
		Pr_InitPara();
		break;

	case ESC_FEED_DOTLINES:
		Pr_DotLines(vPara);
		break;

	case ESC_JUSTIFICATION:
		Pr_SetPara(PRS_JUSTIFICATION, vPara);
		break;

	case ESC_FEED_LINES:
		Pr_TextLines(vPara);
		break;

	default:
		break;
	}

	return vRet;
}

// 左边距与文本区不进行关联，改为在打印阶段再计算实际的文本区。
int Pr_GsDeal(const unsigned char *szContent)
{
	int vRet = 3;
	unsigned char vSubCmd, vPara;
	unsigned int vVal;
	int vWidth, vHeight;

	vSubCmd = szContent[1];
	vPara = szContent[2];
	switch(vSubCmd)
	{
	case GS_REVERSE:
		Pr_SetPara(PRS_REVERSE, vPara);
		break;

	case GS_LEFT_MARGIN:
		vVal = szContent[3];
		vVal = vVal*256+vPara;
		if(vVal < PR_WIDTH_BITS){
			Pr_SetPara(PRS_TEXT_LEFT, vVal);
		}
		vRet = 4;
		break;

	case GS_TEXT_REGION:
		vVal = szContent[3];
		vVal = vVal*256+vPara;
		if(vVal <= PR_WIDTH_BITS){
			Pr_SetPara(PRS_TEXT_REGION, vVal);
		}
		vRet = 4;
		break;

	case GS_MONO_DATA:
		vWidth = szContent[2] + szContent[3]*256;
		vHeight = szContent[4] + szContent[5]*256;
		Pr_MonoData(vWidth, vHeight, (unsigned char*)(szContent+6));
		vRet = 6+vWidth*vHeight/8;
		break;

	default:
		break;
	}

	return vRet;
}

int Pr_CmdDeal(const unsigned char *szContent)
{
	int vRet = 0;
	unsigned char vCmd;

	vCmd = szContent[0];
	switch(vCmd)
	{
	case PRC_ESC:
		vRet = Pr_EscDeal(szContent);
		break;

	case PRC_GS:
		vRet = Pr_GsDeal(szContent);
		break;

	default:
		break;
	}

	return vRet;
}


int Pr_GetTextLen(const char *strText, int vMaxLen, int *pvTextLen)
{
	int vRet = 0;
	int i;
	int vTextLen = 0;

	for(i=0; i<vMaxLen; i++){
		if((strText[i] == PRC_ESC) || (strText[i] == PRC_GS)){
			break;
		}
		else if(strText[i] == '\n'){
			vRet = 1;
			break;
		}
		else if(strText[i] == '\r'){
			vRet = 1;
			if((i+1 < vMaxLen) && (strText[i+1] == '\n')){
				vRet += 1;
			}
			break;
		}
		vTextLen += 1;
	}
	*pvTextLen = vTextLen;

	return vRet;
}

int Pr_TextDeal(const char *strBuf, int vLen)
{
	int vRet = 0;
	int vRes;
	char *strText = NULL;

	strText = malloc(vLen+1);
	if(strText == NULL){
		vRet = -1;
		goto LB_END;
	}

	memcpy(strText, strBuf, vLen);
	strText[vLen] = '\0';
	vRes = Pr_Text(strText);
	if(vRes != 0){
		vRet = -2;
		goto LB_END;
	}

LB_END:
	if(strText != NULL){
		free(strText);
	}
	return vRet;
}

int Pr_Flow(void *pvStrem, int vLen)
{
	int vRet = 0;
	const unsigned char *strText=pvStrem;
	int vTextInd = 0;
	int vIsCmd, vTextEnd;
	int vStep = 0;
	int vTextLen = 0;

	while(vTextInd<vLen){
		vIsCmd = Pr_IsCmdCode(strText+vTextInd);
		if(vIsCmd == 0){
			vTextEnd = Pr_IsTextEnd(strText+vTextInd);
			if(vTextEnd == 0){
				// 文本处理
				vStep = Pr_GetTextLen((char*)(strText+vTextInd), vLen-vTextInd, &vTextLen);
				vRet = Pr_TextDeal((char*)(strText+vTextInd), vTextLen);
				if(vRet != 0){
					goto LB_END;
				}
				vStep += vTextLen;
			}
			else{
				// 换行处理
				vRet = Pr_TextLines(1);
				if(vRet != 0){
					goto LB_END;
				}
				vStep = vTextEnd;
			}
		}
		else{
			// 指令处理
			vStep = Pr_CmdDeal(strText+vTextInd);
		}
		vTextInd += vStep;
	}

LB_END:
	if(vRet != 0){
		PrPrintf("Pr_Flow: %d\r\n", vRet);
	}
	return vRet;
}

int Pr_Format(const char *strFmt, ...)
{
	va_list args;
	int vRet;
	int printed;
	unsigned char szLog[1024];

	va_start(args, strFmt);
	printed = vsnprintf((char*)szLog, sizeof(szLog)-1, strFmt, args);
	va_end(args);

	vRet = Pr_Flow(szLog, printed);

	return vRet;
}

