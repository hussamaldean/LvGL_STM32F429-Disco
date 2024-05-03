#include "ILI9341.h"
#include "LCD_Pins.h"
#include "stdlib.h"




//initialize the tft
void ILI9341_Init(void)
{
	LCD_RST();


//	LCD_Write_Cmd(0xCA);
//	LCD_Write_Data(0xC3);
//	LCD_Write_Data(0x08);
//	LCD_Write_Data(0x50);
//
//	LCD_Write_Cmd(ILI9341_POWERB);
//	delay(10);
//	LCD_Write_Data(0x00);;
//	LCD_Write_Data(0xC1);
//	LCD_Write_Data(0x30);
//
//
//	LCD_Write_Cmd(ILI9341_POWER_SEQ);
//	LCD_Write_Data(0x64);
//	LCD_Write_Data(0x03);
//	LCD_Write_Data(0X12);
//	LCD_Write_Data(0X81);
//
//
//	LCD_Write_Cmd(ILI9341_DTCA);
//	LCD_Write_Data(0x85);
//	LCD_Write_Data(0x00);
//	LCD_Write_Data(0x7A);
//
//
//	LCD_Write_Cmd(ILI9341_POWERA);
//	LCD_Write_Data(0x39);
//	LCD_Write_Data(0x2C);
//	LCD_Write_Data(0x00);
//	LCD_Write_Data(0x34);
//	LCD_Write_Data(0x02);
//
//
//	LCD_Write_Cmd(ILI9341_PRC);
//	LCD_Write_Data(0x20);
//
//
//	LCD_Write_Cmd(ILI9341_DTCB);
//	LCD_Write_Data(0x00);
//	LCD_Write_Data(0x00);
//
//
//	LCD_Write_Cmd(ILI9341_POWER1);
//	LCD_Write_Data(0x10);
//
//
//	LCD_Write_Cmd(ILI9341_POWER2);
//	LCD_Write_Data(0x10);
//
//
//	LCD_Write_Cmd(ILI9341_VCOM1);
//	LCD_Write_Data(0x45);
//	LCD_Write_Data(0x15);
//
//
//	LCD_Write_Cmd(ILI9341_VCOM2);
//	LCD_Write_Data(0X90);
//
//
//
//	LCD_Write_Cmd(ILI9341_PIXEL_FORMAT);
//	LCD_Write_Data(0x55); //select RGB666
//
//	LCD_Write_Cmd(ILI9341_FRMCTR1);
//	LCD_Write_Data(0x00);
//	LCD_Write_Data(0x1B);//frame rate = 70
//
//
//	LCD_Write_Cmd(ILI9341_DFC);    // Display Function Control
//	LCD_Write_Data(0x0A);
//	LCD_Write_Data(0xA7);
//	LCD_Write_Data(0x27);
//	LCD_Write_Data(0x04);
//
//
//	LCD_Write_Cmd(ILI9341_3GAMMA_EN);    // 3Gamma Function Disable
//	LCD_Write_Data(0x00);
//
//
//	LCD_Write_Cmd(ILI9341_GAMMA);
//	LCD_Write_Data(0x01);
//
//
//	LCD_Write_Cmd(ILI9341_PGAMMA);    //Set Gamma
//	LCD_Write_Data(0x0F);
//	LCD_Write_Data(0x29);
//	LCD_Write_Data(0x24);
//	LCD_Write_Data(0x0C);
//	LCD_Write_Data(0x0E);
//	LCD_Write_Data(0x09);
//	LCD_Write_Data(0x4E);
//	LCD_Write_Data(0x78);
//	LCD_Write_Data(0x3C);
//	LCD_Write_Data(0x09);
//	LCD_Write_Data(0x13);
//	LCD_Write_Data(0x05);
//	LCD_Write_Data(0x17);
//	LCD_Write_Data(0x11);
//	LCD_Write_Data(0x00);
//
//
//	LCD_Write_Cmd(ILI9341_NGAMMA);
//	LCD_Write_Data(0x00);
//	LCD_Write_Data(0x18);
//	LCD_Write_Data(0x1D);
//	LCD_Write_Data(0x02);
//	LCD_Write_Data(0x0F);
//	LCD_Write_Data(0x04);
//	LCD_Write_Data(0x36);
//	LCD_Write_Data(0x13);
//	LCD_Write_Data(0x4C);
//	LCD_Write_Data(0x07);
//	LCD_Write_Data(0x13);
//	LCD_Write_Data(0x0F);
//	LCD_Write_Data(0x2E);
//	LCD_Write_Data(0x2F);
//	LCD_Write_Data(0x05);
//
//	LCD_Write_Cmd(ILI9341_RGB_INTERFACE);
//	LCD_Write_Data(0xC2); //Data is fetched during falling edge of DOTCLK
//
//
//	LCD_Write_Cmd(ILI9341_INTERFACE);
//	LCD_Write_Data(0x01);
//	LCD_Write_Data(0x00);
//	LCD_Write_Data(0x06);
//
//
////	LCD_Write_Cmd(ILI9341_MAC);    // Memory Access Control command
////	LCD_Write_Data(0x08);
//
////	LCD_Write_Cmd(ILI9341_ETMOD);
////	LCD_Write_Data(0x07);
////
////	LCD_Write_Cmd(ILI9341_WCD);
////	LCD_Write_Data(0xFF);
////
////	LCD_Write_Cmd(ILI9341_WDB);
////	LCD_Write_Data(0x20);
//
//
//	LCD_Write_Cmd(ILI9341_SLEEP_OUT); //Exit Sleep
//	delay(100);
//	LCD_Write_Cmd(ILI9341_DISPLAY_ON); //display on
//	delay(100);
//
//	LCD_Write_Cmd(ILI9341_GRAM);
//	delay(200);



	LCD_Write_Cmd(0xCA);
	  LCD_Write_Data(0xC3);
	  LCD_Write_Data(0x08);
	  LCD_Write_Data(0x50);

	  LCD_Write_Cmd(LCD_POWERB);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0xC1);
	  LCD_Write_Data(0x30);

	  LCD_Write_Cmd(LCD_POWER_SEQ);
	  LCD_Write_Data(0x64);
	  LCD_Write_Data(0x03);
	  LCD_Write_Data(0x12);
	  LCD_Write_Data(0x81);

	  LCD_Write_Cmd(LCD_DTCA);
	  LCD_Write_Data(0x85);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x78);

	  LCD_Write_Cmd(LCD_POWERA);
	  LCD_Write_Data(0x39);
	  LCD_Write_Data(0x2C);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x34);
	  LCD_Write_Data(0x02);

	  LCD_Write_Cmd(LCD_PRC);
	  LCD_Write_Data(0x20);

	  LCD_Write_Cmd(LCD_DTCB);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x00);

	  LCD_Write_Cmd(LCD_FRMCTR1);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x1B);

	  LCD_Write_Cmd(LCD_DFC);
	  LCD_Write_Data(0x0A);
	  LCD_Write_Data(0xA2);

	  LCD_Write_Cmd(LCD_POWER1);
	  LCD_Write_Data(0x10);

	  LCD_Write_Cmd(LCD_POWER2);
	  LCD_Write_Data(0x10);

	  LCD_Write_Cmd(LCD_VCOM1);
	  LCD_Write_Data(0x45);
	  LCD_Write_Data(0x15);

	  LCD_Write_Cmd(LCD_VCOM2);
	  LCD_Write_Data(0x90);

	  LCD_Write_Cmd(LCD_MAC);
	  LCD_Write_Data(0x08);

	  LCD_Write_Cmd(LCD_3GAMMA_EN);
	  LCD_Write_Data(0x00);

	  LCD_Write_Cmd(LCD_RGB_INTERFACE);
	  LCD_Write_Data(0xC2);

	  LCD_Write_Cmd(LCD_DFC);
	  LCD_Write_Data(0x0A);
	  LCD_Write_Data(0xA7);
	  LCD_Write_Data(0x27);
	  LCD_Write_Data(0x04);

	  /* Colomn address set */
	  LCD_Write_Cmd(LCD_COLUMN_ADDR);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0xEF);
	  /* Page address set */
	  LCD_Write_Cmd(LCD_PAGE_ADDR);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x01);
	  LCD_Write_Data(0x3F);

	  LCD_Write_Cmd(LCD_INTERFACE);
	  LCD_Write_Data(0x01);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x06);

	  LCD_Write_Cmd(LCD_GRAM);
	  delay(200);

	  LCD_Write_Cmd(LCD_GAMMA);
	  LCD_Write_Data(0x01);

	  LCD_Write_Cmd(LCD_PGAMMA);
	  LCD_Write_Data(0x0F);
	  LCD_Write_Data(0x29);
	  LCD_Write_Data(0x24);
	  LCD_Write_Data(0x0C);
	  LCD_Write_Data(0x0E);
	  LCD_Write_Data(0x09);
	  LCD_Write_Data(0x4E);
	  LCD_Write_Data(0x78);
	  LCD_Write_Data(0x3C);
	  LCD_Write_Data(0x09);
	  LCD_Write_Data(0x13);
	  LCD_Write_Data(0x05);
	  LCD_Write_Data(0x17);
	  LCD_Write_Data(0x11);
	  LCD_Write_Data(0x00);
	  LCD_Write_Cmd(LCD_NGAMMA);
	  LCD_Write_Data(0x00);
	  LCD_Write_Data(0x16);
	  LCD_Write_Data(0x1B);
	  LCD_Write_Data(0x04);
	  LCD_Write_Data(0x11);
	  LCD_Write_Data(0x07);
	  LCD_Write_Data(0x31);
	  LCD_Write_Data(0x33);
	  LCD_Write_Data(0x42);
	  LCD_Write_Data(0x05);
	  LCD_Write_Data(0x0C);
	  LCD_Write_Data(0x0A);
	  LCD_Write_Data(0x28);
	  LCD_Write_Data(0x2F);
	  LCD_Write_Data(0x0F);

	  LCD_Write_Cmd(LCD_SLEEP_OUT);
	  delay(200);
	  LCD_Write_Cmd(LCD_DISPLAY_ON);
	  /* GRAM start writing */
	  LCD_Write_Cmd(LCD_GRAM);
}


