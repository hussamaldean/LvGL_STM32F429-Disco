/*********************
 *      INCLUDES
 *********************/
#include "LCDController.h"
#include <stdbool.h>
#include "ILI9341.h"
#include "stm32f4xx.h"
#include "stdint.h"
#include "ltdc.h"
/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES 240


#define MY_DISP_VER_RES 320

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/

/**********************
 *  STATIC VARIABLES
 **********************/
#define buffer_size 64

static lv_disp_draw_buf_t draw_buf_dsc_1;

static lv_color_t buf_1[MY_DISP_HOR_RES*buffer_size]__attribute__ ((section (".SDRAM_data")));
static lv_color_t buf_2[MY_DISP_HOR_RES*buffer_size]__attribute__ ((section (".SDRAM_data")));

/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /*A buffer for 320 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, buf_2, MY_DISP_HOR_RES*buffer_size);   /*Initialize the display buffer*/
    //lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES*buffer_size);   /*Initialize the display buffer*/



    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/


    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;
    disp_drv.direct_mode=0;
    disp_drv.antialiasing=1;
    disp_drv.full_refresh=0;
    disp_drv.dpi=167;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_1;


    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    ILI9341_Init();

    LTDC_Init();
    Layer_Init(LTDC_Layer1);

}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}


static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t  *color_p)
{

	  lv_coord_t width = lv_area_get_width(area);
	  lv_coord_t height = lv_area_get_height(area);

	  DMA2D->CR = 0x00U << DMA2D_CR_MODE_Pos;

	  DMA2D->FGPFCCR = DMA2D_FGPFCCR_CM_1; /*RGB565*/

	  DMA2D->FGMAR = (uint32_t)color_p;

	  DMA2D->FGOR = 0;

	  DMA2D->OPFCCR = DMA2D_OPFCCR_CM_1; /*RGB565*/

	  DMA2D->OMAR =  (lcd_get_fb_address())+2*(area->y1 * MY_DISP_HOR_RES + area->x1);

	  DMA2D->OOR =MY_DISP_HOR_RES - width;

	  DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);

	  DMA2D->IFCR = DMA2D_IFCR_CTCIF;

	  DMA2D->CR |= DMA2D_CR_TCIE;

	  DMA2D->CR |= DMA2D_CR_START;



}

void DMA2D_IRQHandler(void)
{
	if((DMA2D->ISR & DMA2D_ISR_TCIF) == DMA2D_ISR_TCIF)
	{
	    /*IMPORTANT!!!
	     *Inform the graphics library that you are ready with the flushing*/
		lv_disp_flush_ready(&disp_drv);


		DMA2D->IFCR|=DMA2D_IFCR_CTCIF;
	}
}
