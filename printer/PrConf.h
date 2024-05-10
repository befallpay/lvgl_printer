#ifndef _PR_CONF_H
#define _PR_CONF_H


#define PR_LVGL_DEBUG


#ifdef PR_LVGL_DEBUG

#include <stdio.h>

#define PrPrintf	printf

int Bmp16_ToFile(const char *strName, int vWidth, int vHeight, unsigned char *szData);

#else

#define PrPrintf

#endif // PR_LVGL_DEBUG


#endif
