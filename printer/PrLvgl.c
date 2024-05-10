#include "lvgl.h"
#include "PrConf.h"
#include "PrInput.h"
#include "PrWraper.h"
#include "PrPara.h"
#include "PrLvgl.h"


typedef struct {
    const char * name;  /* The name of the font file */
    lv_font_t * font;   /* point to lvgl font */
    uint16_t weight;    /* font size */
    uint16_t style;     /* font style */
}CPrFont;
static CPrFont s_tPrFont = {NULL, NULL, 0, 0};


int Pr_SetFont(char *strName, int vSize, int vStyle)
{
	int vRet = 0;

	if(s_tPrFont.font != NULL){
		lv_tiny_ttf_destroy(s_tPrFont.font);
		s_tPrFont.font = NULL;
	}

	memset(&s_tPrFont, 0, sizeof(CPrFont));
	s_tPrFont.name = strName;
    s_tPrFont.weight = vSize;
	// tiny_ttf不支持这个参数
    s_tPrFont.style = vStyle;
    s_tPrFont.font = lv_tiny_ttf_create_file(strName, vSize);
	if(s_tPrFont.font == NULL) {
        vRet = -1;
    }

    return vRet;
}

int Pr_Text(const char *strText)
{
	int vRet = 0;
	CPrPara tPara;

	lv_draw_label_dsc_t label_dsc;
	lv_point_t txt_size = {0};
	lv_area_t coords = {0};

	unsigned char *szCanvas = NULL;
	int vSize;
    lv_obj_t * canvas = NULL;

	lv_layer_t layer;

	Pr_ReadPara(&tPara);
	// 计算文本的点阵高度
	lv_text_get_size(&txt_size, strText, s_tPrFont.font, 0, 0, PR_WIDTH_BITS, LV_TEXT_FLAG_NONE);
	// to do...根据打印机设置配置文本区域
	coords.x1 = tPara.vTextLeft;
	coords.y1 = 0;
	coords.x2 = tPara.vTextLeft+tPara.vTextRegion-1;
	if(coords.x2 > PR_WIDTH_BITS-1){
		coords.x2 = PR_WIDTH_BITS-1;
	}
	coords.y2 = txt_size.y-1;

	vSize = LV_CANVAS_BUF_SIZE(PR_WIDTH_BITS, txt_size.y, 16, 4);
	szCanvas = malloc(vSize);
	if(szCanvas == NULL){
		vRet = -2;
		goto LB_END;
	}

	canvas = lv_canvas_create(lv_screen_active());
	lv_canvas_set_buffer(canvas, szCanvas, PR_WIDTH_BITS, txt_size.y, LV_COLOR_FORMAT_RGB565);
	lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);

    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.text = strText;
	label_dsc.font = s_tPrFont.font;
	label_dsc.line_space = tPara.vLineSpace+tPara.vUnderline;
	label_dsc.align = tPara.vJustification;
	if(tPara.vUnderline != 0){
		label_dsc.decor = LV_TEXT_DECOR_UNDERLINE;
	}
	//label_dsc.sel_bg_color = lv_color_white();

    lv_canvas_init_layer(canvas, &layer);
    lv_draw_label(&layer, &label_dsc, &coords);
    lv_canvas_finish_layer(canvas, &layer);

	Pr_Write(txt_size.y, szCanvas);

LB_END:
#ifdef PR_LVGL_DEBUG
    Bmp16_ToFile("text.bmp", PR_WIDTH_BITS, txt_size.y, szCanvas);
#else
    if(canvas != NULL){
        lv_obj_del(canvas);
    }
	if(szCanvas != NULL){
		free(szCanvas);
	}
#endif
	return vRet;
}

int Pr_Image(const char *strImgPath)
{
	int vRet = 0;
	CPrPara tPara;

	lv_image_header_t header;
	lv_area_t coords = {0};
	lv_result_t res;

	unsigned char *szCanvas = NULL;
	int vSize;
    lv_obj_t * canvas = NULL;

	lv_layer_t layer;
	lv_draw_image_dsc_t dsc;

	Pr_ReadPara(&tPara);
	// get image w and h
	res = lv_image_decoder_get_info(strImgPath, &header);
	if(res != LV_RESULT_OK){
		vRet = -1;
		goto LB_END;
	}
	// align
	coords.x1 = 0;
	coords.x2 = header.w-1;
	coords.y1 = 0;
	coords.y2 = header.h-1;
	if(tPara.vJustification == PRSV_JUST_MID){
		coords.x1 = (PR_WIDTH_BITS-header.w)>>1;
		coords.x2 = coords.x1+header.w-1;
	}
	else if(tPara.vJustification == PRSV_JUST_RIGHT){
		coords.x1 = (PR_WIDTH_BITS-header.w);
		coords.x2 = PR_WIDTH_BITS-1;
	}

	vSize = LV_CANVAS_BUF_SIZE(PR_WIDTH_BITS, header.h, 16, 4);
	szCanvas = malloc(vSize);
	if(szCanvas == NULL){
		vRet = -2;
		goto LB_END;
	}

	canvas = lv_canvas_create(lv_scr_act());
	lv_canvas_set_buffer(canvas, szCanvas, PR_WIDTH_BITS, header.h, LV_COLOR_FORMAT_RGB565);
	lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);

    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_init(&dsc);
    dsc.src = strImgPath;
    lv_draw_image(&layer, &dsc, &coords);

	lv_canvas_finish_layer(canvas, &layer);

	Pr_Write(header.h, szCanvas);

LB_END:
#ifdef PR_LVGL_DEBUG
    Bmp16_ToFile("image.bmp", PR_WIDTH_BITS, header.h, szCanvas);
#else
    if(canvas != NULL){
        lv_obj_del(canvas);
    }
	if(szCanvas != NULL){
		free(szCanvas);
	}
#endif
	return vRet;
}

