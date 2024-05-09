#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PrLvgl.h"
#include "PrWraper.h"


int print_text(void)
{
    Pr_SetFont("P:hmny.ttf", 24, 0);

	Pr_Open();
	Pr_Text("1234567890abcdefghijklmn1234567890ABCDEFGHIJKLMN");
	Pr_Close();

	return 0;
}

int print_image(void)
{
    Pr_SetFont("P:hmny.ttf", 24, 0);

	Pr_Open();
	Pr_ImageAt("P:text.bmp", 0, 0);
	Pr_Close();

	return 0;
}