/*
 * TouchController.c
 *
 *  Created on: Nov 16, 2023
 *      Author: hussamaldean
 */



/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "TouchController.h"
#include "STMPE811.h"
#include "ILI9341.h"
/*********************
 *      DEFINES
 *********************/
#define GUI_WIDTH 240
#define GUI_HEIGHT 320
/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);


/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;

struct {
	lv_coord_t x;
	lv_coord_t y;
}get_xy;

uint16_t intx, inty;


//static void ConvSTMPtoILI(uint16_t *x, uint16_t *y)
//{
//	int16_t tx,ty;
//	tx = (int16_t)(((int32_t)*x - Touch_XMIN) * GUI_WIDTH / Touch_WIDTH);
//	tx = (tx < 0) ? 0 : tx;
//	tx = (tx >= GUI_WIDTH) ? GUI_WIDTH-1 : tx;
//	ty = (int16_t)(((int32_t)*y - Touch_YMIN) * GUI_HEIGHT / Touch_HEIGHT);
//	ty = (ty < 0) ? 0 : ty;
//	ty = (ty >= GUI_HEIGHT) ? GUI_HEIGHT-1 : ty;
//	*x = tx;
//	*y = ty;
//}


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{

    static lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    touchpad_init();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);


}

/*Initialize your touchpad*/
static void touchpad_init(void)
{
	STMPE811_Touch_Enable();
}



uint8_t ret_value;
static int32_t _x = 0, _y = 0;
int16_t xDiff, yDiff, xr, yr;
uint16_t x_raw, y_raw;

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{



	if(isToched()==no_touch)
	{
		ret_value=false;
	}
	else
	{
			getTouchValue(&x_raw,&y_raw);
			/* Y value first correction */
			y_raw -= 300;

			/* Y value second correction */
			yr = y_raw / 11;

			/* Return y_raw position value */
			if(yr <= 0) yr = 0;
			else if (yr > GUI_HEIGHT) yr = GUI_HEIGHT - 1;

			y_raw = yr;

			/* X value first correction */
			if(x_raw <= 3720) x_raw = 3770 - x_raw;
			else  x_raw = 3770 - x_raw;

			/* X value second correction */
			xr = x_raw / 15;

			/* Return X position value */
			if(xr <= 0) xr = 0;
			else if (xr > GUI_WIDTH) xr = GUI_WIDTH - 1;

			x_raw = xr;
			if(x_raw>_x){xDiff=x_raw - _x;}
			else {xDiff=_x - x_raw;}

			if(y_raw>_y){yDiff=y_raw - _y;}
			else {yDiff=_y - y_raw;}


			//xDiff = x_raw > _x? (x_raw - _x): (_x - x_raw);
			//yDiff = y_raw > _y? (y_raw - _y): (_y - y_raw);

			if (xDiff + yDiff > 5)
			{
				_x = x_raw;
				_y = y_raw;
			}

			get_xy.x = GUI_WIDTH-_x;
			get_xy.y = GUI_HEIGHT-_y;
			ret_value= true;
	}
	return ret_value;
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{

    /*Save the pressed coordinates and the state*/
    if(touchpad_is_pressed()) {

        data->state = LV_INDEV_STATE_PR;

    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the last pressed coordinates*/
    data->point.x = get_xy.x;
    data->point.y = get_xy.y;
}


/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    /*Your code comes here*/

    (*x) = 0;
    (*y) = 0;
}



