#ifndef _PR_CMD_H
#define _PR_CMD_H


// main cmd
#define PRC_ESC				0x1b
#define PRC_GS				0x1d

// subcmd ESC
#define ESC_UNDERLINE 			0x2d
#define ESC_LINE_SPACE			0x33
#define ESC_INITIALIZE 			0x40
#define ESC_FEED_DOTLINES 		0x4a
#define ESC_JUSTIFICATION 		0x61
#define ESC_FEED_LINES 			0x64

// subcmd GS
#define GS_REVERSE				0x42
#define GS_LEFT_MARGIN			0x4C
#define GS_TEXT_REGION			0x57

#define GS_BITMAP_DOWM			0x2a
#define GS_BITMAP_DEL			0x2b
#define GS_BITMAP_PRINT			0x2f
#define GS_BITMAP_DATA			0x30

#define GS_IMAGE_FILE			0x70
#define GS_MONO_DATA			0x71


int Pr_Flow(void *pvStrem, int vLen);
int Pr_Format(const char *strFmt, ...);


#endif

