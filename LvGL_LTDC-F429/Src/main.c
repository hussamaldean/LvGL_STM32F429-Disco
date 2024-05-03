#include "LCD_Pins.h"
#include "ILI9341.h"
#include "i2c3.h"
#include "STMPE811.h"
#include "exti.h"
#include "stdio.h"
#include "LCDController.h"
#include "lvgl/demos/benchmark/lv_demo_benchmark.h"
#include "lvgl/demos/lv_demos.h"
#include "TouchController.h"
#include "lvgl/examples/lv_examples.h"
#include "LTDC.h"
#include "colors.h"
#include "DMA2D.h"
#include "SDRAM.h"
#include "ui/ui.h"
#include "LED.h"
#include "adc.h"
#include "PWM.h"


uint64_t previousMillis_ADC,previousMillis_LvGL;
int main(void)
{
	delay_init(180000000);

	SDRAM_Pins_Init();
	FMC_Clock_Enable();
	SDRAM_Init();
	LEDS_Init();
	PA5_ADC_Init();
	PB3_PWM_Init();
	i2c3_init();

	LCD_Pin_Init();
	LCD_SPI_Init();
	LTDC_Pins_Init();


	DMA2_Init();


	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();

	lv_demo_widgets();
	//lv_demo_benchmark();
	//lv_demo_music();


	//ui_init();



	while(1)
	{



		if(millis()-previousMillis_ADC>200)
		{
			lv_arc_set_value(ui_Arc1, PA5_ADC_Value());
			previousMillis_ADC=millis();
		}

		if(millis()-previousMillis_LvGL>5)
		{
			lv_timer_handler();
			previousMillis_LvGL=millis();
		}



	}
}
