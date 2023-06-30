#ifndef __LCD_H__
#define __LCD_H__
/***********************************************************************************************************************************
    *	@file  	  w25qxx.c
	*   @date     2020-08-17		
	*	@author   魔女开发板   老周
    *   @brief    代码分享     Q群文件夹：262901124  自由下载
    *   @taobao   淘宝硬件     ttps://demoboard.taobao.com/
    ********************************************************************************************************************************
    ** 1.8寸彩色显示屏模块引脚说明(ST7735)
    ** GND         电源地
    ** VCC         3.3V。不要接5V, 模块不带LDO，5V很易烧屏
    ** SCL/SCK     SPI的SCK引脚  
    ** SDA/DIN     SPI的MOSI引脚 
    ** RES/RST     复位引脚，最好和单片机的复位引脚相接
    ** DC /RS      命令、数据选择引脚
    ** CS /CE      SPI的CS片选引脚
    ** BL /LED     控制背光LED， 高电平亮。引脚已串1K电阻，且已10K上拉。
    **  
    ** 测试硬件    魔女开发板_STM32F103RCT6 + 1.8寸彩屏模块(ST7735)
************************************************************************************************************************************/

/*****************************************************************************
 ** 移植时，只需修改下面的引脚、SPI端口、屏幕参数
*****************************************************************************/
#include "main.h"


#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

// 屏幕参数
#define LCD_WIDTH         160               // 设置屏幕的像素大小，
#define LCD_HEIGHT        128               // 注意：实际像素好像要比标示值大1~2像素，
#define LCD_DIR           4                 // 四种显示方向，参数：1、2、3、4
//  结束 移植修改 ************************************************************

extern uint8_t map[LCD_HEIGHT][LCD_WIDTH];
/*****************************************************************************
 ** 颜色定义， 移植时不用修改
****************************************************************************/
#define WHITE             0xFFFF
#define BLACK             0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE             0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN             0x07E0
#define CYAN             0x7FFF
#define YELLOW             0xFFE0
#define BROWN             0XBC40 //棕色
#define BRRED             0XFC07 //棕红色
#define GRAY             0X8430 //灰色
#define DARKBLUE         0X01CF    //深蓝色
#define LIGHTBLUE         0X7D7C    //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
#define LIGHTGREEN         0X841F //浅绿色
#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY             0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

extern uint16_t colors[255];

/*****************************************************************************
 ** 声明  全局函数； 移植时不用修改
****************************************************************************/
void LCD_Init(
        void);                                                        // LCD驱动ST7735初始化，屏幕参数在本文件顶部修改(移植参数区)，主要是像素尺寸、显示方向
void LCD_Display(u8 sw);                                                    // 显示屏开关， 1：打开屏幕， 0：熄屏
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);                    // 填充单色
void LCD_Line(u16 sX, u16 sY, u16 eX, u16 eY, u16 color);                   // 画线
void LCD_Circle(u16 x0, u16 y0, u8 r, u16 color);                                // 画圆
void LCD_Image(u16 x, u16 y, u16 width, u16 height, const u8 *image);       // 显示图片
// 任意字符、汉字显示：字符数据在font.h文件中，汉字数据在W25Q128文件中，适合任意汉字输出；宋体：12、16、24、32号
void
LCD_String(u16 x, u16 y, char *pFont, u8 size, u32 fColor, u32 bColor);  // 显示中英字符串；左上角坐标x, 左上角坐标y, 字库缓存地址，字号大小，字色，底色
void
mLCD_String(u16 x, u16 y, char *pFont, u8 size, u32 fColor, u32 bColor);  // 显示中英字符串；左上角坐标x, 左上角坐标y, 字库缓存地址，字号大小，字色，底色
void drawPoint(u16 x, u16 y, u16 color);

// 特定汉字显示:字库数据在font文件中.只能保存少量字库，适合固定输出
void
LCD_Chinese(u32 x, u32 y, u8 index, u8 size, u16 fColor, u16 bColor);  // 显示1个16号汉字；左上角坐标x, 左上角坐标y, 字库数据在缓存中的位置，字色，底色
void
LCD_Chinese32ForFile(u32 x, u32 y, u8 index, u16 fColor, u16 bColor);  // 显示1个32号汉字；左上角坐标x, 左上角坐标y, 字库数据在缓存中的位置，字色，底色
//void LCD_GUI(void);
#endif  
