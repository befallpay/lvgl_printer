#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PrPara.h"
#include "PrLvgl.h"
#include "PrWraper.h"
#include "PrCmd.h"


int print_text(void)
{
    Pr_SetFont("P:hmny.ttf", 24, 0);

	Pr_Open();
	Pr_SetPara(PRS_UNDERLINE, 1);
	Pr_Text("1234567890abcdefghijklmn1234567890ABCDEFGHIJKLMN");
	Pr_SetPara(PRS_UNDERLINE, 0);
	Pr_Close();

	return 0;
}

int print_image(void)
{
    Pr_SetFont("P:hmny.ttf", 24, 0);

	Pr_Open();
	Pr_SetPara(PRS_JUSTIFICATION, PRSV_JUST_MID);
	Pr_Image("P:text.bmp");
	Pr_SetPara(PRS_JUSTIFICATION, PRSV_JUST_LEFT);
	Pr_Close();

	return 0;
}

int print_format(void)
{
    Pr_SetFont("P:hmny.ttf", 24, 0);

	Pr_Open();
	Pr_Format("%c%c%c1234567890\n%c%c%cabcdefghijklmn\n%c%c%c1234567890\n%c%c%cABCDEFGHIJKLMN\n%c%c",
				PRC_ESC, ESC_JUSTIFICATION, PRSV_JUST_MID,
				PRC_ESC, ESC_JUSTIFICATION, PRSV_JUST_RIGHT,
				PRC_ESC, ESC_JUSTIFICATION, PRSV_JUST_LEFT,
				PRC_ESC, ESC_UNDERLINE, 1,
				PRC_ESC, ESC_INITIALIZE);
	Pr_Close();

	return 0;
}



