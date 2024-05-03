#ifndef ILI9341_H_
#define ILI9341_H_

//List of includes
#include "delay.h"



//LCD dimensions defines
#define ILI9341_WIDTH       320
#define ILI9341_HEIGHT      240


#define ILI9341_PIXEL_COUNT	ILI9341_WIDTH * ILI9341_HEIGHT


#define  ILI9341_HSYNC            ((uint32_t)9)   /* Horizontal synchronization */
#define  ILI9341_HBP              ((uint32_t)29)    /* Horizontal back porch      */
#define  ILI9341_HFP              ((uint32_t)2)    /* Horizontal front porch     */
#define  ILI9341_VSYNC            ((uint32_t)1)   /* Vertical synchronization   */
#define  ILI9341_VBP              ((uint32_t)3)    /* Vertical back porch        */
#define  ILI9341_VFP              ((uint32_t)2)    /* Vertical front porch       */

/**
  * @brief  ILI9341 Registers
  */

/* Level 1 Commands */
/* Level 1 Commands */
#define ILI9341_SWRESET             0x01U   /* Software Reset */
#define ILI9341_READ_DISPLAY_ID     0x04U   /* Read display identification information */
#define ILI9341_RDDST               0x09U   /* Read Display Status */
#define ILI9341_RDDPM               0x0AU   /* Read Display Power Mode */
#define ILI9341_RDDMADCTL           0x0BU   /* Read Display MADCTL */
#define ILI9341_RDDCOLMOD           0x0CU   /* Read Display Pixel Format */
#define ILI9341_RDDIM               0x0DU   /* Read Display Image Format */
#define ILI9341_RDDSM               0x0EU   /* Read Display Signal Mode */
#define ILI9341_RDDSDR              0x0FU   /* Read Display Self-Diagnostic Result */
#define ILI9341_SPLIN               0x10U   /* Enter Sleep Mode */
#define ILI9341_SLEEP_OUT           0x11U   /* Sleep out register */
#define ILI9341_PTLON               0x12U   /* Partial Mode ON */
#define ILI9341_NORMAL_MODE_ON      0x13U   /* Normal Display Mode ON */
#define ILI9341_DINVOFF             0x20U   /* Display Inversion OFF */
#define ILI9341_DINVON              0x21U   /* Display Inversion ON */
#define ILI9341_GAMMA               0x26U   /* Gamma register */
#define ILI9341_DISPLAY_OFF         0x28U   /* Display off register */
#define ILI9341_DISPLAY_ON          0x29U   /* Display on register */
#define ILI9341_CASET               0x2AU   /* Column address register */
#define ILI9341_RASET               0x2BU   /* Page address register */
#define ILI9341_GRAM                0x2CU   /* GRAM register */
#define ILI9341_RGBSET              0x2DU   /* Color SET */
#define ILI9341_RAMRD               0x2EU   /* Memory Read */
#define ILI9341_PLTAR               0x30U   /* Partial Area */
#define ILI9341_VSCRDEF             0x33U   /* Vertical Scrolling Definition */
#define ILI9341_TEOFF               0x34U   /* Tearing Effect Line OFF */
#define ILI9341_TEON                0x35U   /* Tearing Effect Line ON */
#define ILI9341_MAC                 0x36U   /* Memory Access Control register*/
#define ILI9341_VSCRSADD            0x37U   /* Vertical Scrolling Start Address */
#define ILI9341_IDMOFF              0x38U   /* Idle Mode OFF */
#define ILI9341_IDMON               0x39U   /* Idle Mode ON */
#define ILI9341_PIXEL_FORMAT        0x3AU   /* Pixel Format register */
#define ILI9341_WRITE_MEM_CONTINUE  0x3CU   /* Write Memory Continue */
#define ILI9341_READ_MEM_CONTINUE   0x3EU   /* Read Memory Continue */
#define ILI9341_SET_TEAR_SCANLINE   0x44U   /* Set Tear Scanline */
#define ILI9341_GET_SCANLINE        0x45U   /* Get Scanline */
#define ILI9341_WDB                 0x51U   /* Write Brightness Display register */
#define ILI9341_RDDISBV             0x52U   /* Read Display Brightness */
#define ILI9341_WCD                 0x53U   /* Write Control Display register*/
#define ILI9341_RDCTRLD             0x54U   /* Read CTRL Display */
#define ILI9341_WRCABC              0x55U   /* Write Content Adaptive Brightness Control */
#define ILI9341_RDCABC              0x56U   /* Read Content Adaptive Brightness Control */
#define ILI9341_WRITE_CABC          0x5EU   /* Write CABC Minimum Brightness */
#define ILI9341_READ_CABC           0x5FU   /* Read CABC Minimum Brightness */
#define ILI9341_READ_ID1            0xDAU   /* Read ID1 */
#define ILI9341_READ_ID2            0xDBU   /* Read ID2 */
#define ILI9341_READ_ID3            0xDCU   /* Read ID3 */

/* Level 2 Commands */
#define ILI9341_RGB_INTERFACE       0xB0U   /* RGB Interface Signal Control */
#define ILI9341_FRMCTR1             0xB1U   /* Frame Rate Control (In Normal Mode) */
#define ILI9341_FRMCTR2             0xB2U   /* Frame Rate Control (In Idle Mode) */
#define ILI9341_FRMCTR3             0xB3U   /* Frame Rate Control (In Partial Mode) */
#define ILI9341_INVTR               0xB4U   /* Display Inversion Control */
#define ILI9341_BPC                 0xB5U   /* Blanking Porch Control register */
#define ILI9341_DFC                 0xB6U   /* Display Function Control register */
#define ILI9341_ETMOD               0xB7U   /* Entry Mode Set */
#define ILI9341_BACKLIGHT1          0xB8U   /* Backlight Control 1 */
#define ILI9341_BACKLIGHT2          0xB9U   /* Backlight Control 2 */
#define ILI9341_BACKLIGHT3          0xBAU   /* Backlight Control 3 */
#define ILI9341_BACKLIGHT4          0xBBU   /* Backlight Control 4 */
#define ILI9341_BACKLIGHT5          0xBCU   /* Backlight Control 5 */
#define ILI9341_BACKLIGHT7          0xBEU   /* Backlight Control 7 */
#define ILI9341_BACKLIGHT8          0xBFU   /* Backlight Control 8 */
#define ILI9341_POWER1              0xC0U   /* Power Control 1 register */
#define ILI9341_POWER2              0xC1U   /* Power Control 2 register */
#define ILI9341_VCOM1               0xC5U   /* VCOM Control 1 register */
#define ILI9341_VCOM2               0xC7U   /* VCOM Control 2 register */
#define ILI9341_NVMWR               0xD0U   /* NV Memory Write */
#define ILI9341_NVMPKEY             0xD1U   /* NV Memory Protection Key */
#define ILI9341_RDNVM               0xD2U   /* NV Memory Status Read */
#define ILI9341_READ_ID4            0xD3U   /* Read ID4 */
#define ILI9341_PGAMMA              0xE0U   /* Positive Gamma Correction register */
#define ILI9341_NGAMMA              0xE1U   /* Negative Gamma Correction register */
#define ILI9341_DGAMCTRL1           0xE2U   /* Digital Gamma Control 1 */
#define ILI9341_DGAMCTRL2           0xE3U   /* Digital Gamma Control 2 */
#define ILI9341_INTERFACE           0xF6U   /* Interface control register */

/* Extend register commands */
#define ILI9341_POWERA               0xCBU   /* Power control A register */
#define ILI9341_POWERB               0xCFU   /* Power control B register */
#define ILI9341_DTCA                 0xE8U   /* Driver timing control A */
#define ILI9341_DTCB                 0xEAU   /* Driver timing control B */
#define ILI9341_POWER_SEQ            0xEDU   /* Power on sequence register */
#define ILI9341_3GAMMA_EN            0xF2U   /* 3 Gamma enable register */
#define ILI9341_PRC                  0xF7U   /* Pump ratio control register */

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

/* Size of read registers */
#define LCD_READ_ID4_SIZE        3      /* Size of Read ID4 */


#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_RGBSET              0x2D   /* Color SET */
#define LCD_RAMRD               0x2E   /* Memory Read */
#define LCD_PLTAR               0x30   /* Partial Area */
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */
#define LCD_TEON                0x35   /* Tearing Effect Line ON */
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */
#define LCD_IDMON               0x39   /* Idle Mode ON */
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */

/* Level 2 Commands */
#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define LCD_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define LCD_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define LCD_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define LCD_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define LCD_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_ID4            0xD3   /* Read ID4 */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */

void ILI9341_Init(void);


#endif
