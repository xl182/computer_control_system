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
#include "lcd.h"
#include "gpio.h"
#include "spi.h"
#include "font.h"
/*****************************************************************************
 ** 液晶控制宏定义, 主要为了简化文件内操作
 *****************************************************************************/
// LCD_CS
#define LCD_CS_LOW LCD_CS_GPIO_Port->BSRR = LCD_CS_Pin << 16
#define LCD_CS_HIGH LCD_CS_GPIO_Port->BSRR = LCD_CS_Pin
//
#define LCD_BL_LOW LCD_BL_GPIO_Port->BSRR = LCD_BL_Pin << 16
#define LCD_BL_HIGH LCD_BL_GPIO_Port->BSRR = LCD_BL_Pin

#define LCD_RS_LOW LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin << 16
#define LCD_RS_HIGH LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin
// LCD_RST
#define LCD_RES_LOW LCD_RES_GPIO_Port->BSRR = LCD_RES_Pin << 16
#define LCD_RES_HIGH LCD_RES_GPIO_Port->BSRR = LCD_RES_Pin


char map[LCD_WIDTH][LCD_HEIGHT] = {0};
/*****************************************************************************
 ** 本地变量
 *****************************************************************************/
struct _LCD              // 结构体：用于保存信息、状态
{
    u8 InitOK;
    u16 width;             // LCD 宽度
    u16 height;             // LCD 高度

    u32 bColor;          // 背景色
} xLCD;

/*****************************************************************************
 ** 本地函数
 ****************************************************************************/
//void gpioInit(void);                                         // 引脚初始化
//void spiInit(void);                                          // SPI通信协议初始化
void sendOrder(u16 order);                                   // 向液晶屏发送：寄存器地址值(指令), 8位
void sendByte(u8 Data);                                    // 向液晶屏发送：数据，8位
void sendShort(u16 Data);                                    // 向液晶屏发送：数据，16位
void setCursor(u16 x_start, u16 y_start, u16 x_end, u16 y_end); // 设置显示区域

// SPI发送传送1字节
u8 spiSendByte(u8 data) {
//    HAL_SPI_Transmit_DMA(&hspi2, &data, 8)
//    DMA1_Channel5->CCR &= ~(1 << 0) ;            //关闭DMA通道5
//
//    DMA1_Channel5->CNDTR = 8;					 //重置传输数据量
//
//    DMA1_Channel5->CMAR = data;									 //重置存储器地址
//
//    DMA1_Channel5->CCR |= 3 << 0;               //开启DMA通道5，使能发送完成中断;

    while ((SPI2->SR & SPI_FLAG_TXE) == RESET) {}
    SPI2->DR = data;
    while ((SPI2->SR & SPI_FLAG_RXNE) == RESET) {}
    return SPI2->DR;
}

/*****************************************************************************
*函  数：LCD_Init
*功  能：初始化lcd
*参  数：为了简化理解、便于移植，参数(屏幕像素、显示方向)在h文件里进行修改
*返回值：无
*备  注：
*****************************************************************************/
void LCD_Init(void) {
    xLCD.InitOK = 0;
    xLCD.bColor = BLACK;

    // 显示方向像素匹配
    if ((LCD_DIR == 1) || (LCD_DIR == 3)) {
        xLCD.width = LCD_WIDTH;       // 屏宽度像素，超过此值驱动芯片会自动换行，注意：如果屏幕右边有花屏，就加大这个值
        xLCD.height = LCD_HEIGHT;        // 屏高度像素， 注意：如果屏幕下面有花屏，就加大这个值
    } else {
        xLCD.width = LCD_HEIGHT;
        xLCD.height = LCD_WIDTH;
    }

    // 初始化GPIO
//    gpioInit();
    MX_GPIO_Init();
    // 初始化SPI外设、协议
//    spiInit();
    MX_SPI2_Init();
    __HAL_SPI_ENABLE(&hspi2);
    LCD_BL_HIGH;

    // 屏幕复位
    LCD_RES_LOW;           // LCD_RST=0	  //SPI接口复位
    HAL_Delay(20);          // delay 20 ms
    LCD_RES_HIGH;        // LCD_RST=1
    HAL_Delay(20);

    sendOrder(0x11);       // 退出睡眠模式
    HAL_Delay(120);         // Delay 120ms
    //------------------------------------ST7735S Frame Rate-----------------------------------------//
    sendOrder(0xB1);
    sendByte(0x05);
    sendByte(0x3C);
    sendByte(0x3C);

    sendOrder(0xB2);
    sendByte(0x05);
    sendByte(0x3C);
    sendByte(0x3C);

    sendOrder(0xB3);
    sendByte(0x05);
    sendByte(0x3C);
    sendByte(0x3C);
    sendByte(0x05);
    sendByte(0x3C);
    sendByte(0x3C);
    //------------------------------------End ST7735S Frame Rate-----------------------------------------//
    sendOrder(0xB4); // Dot inversion
    sendByte(0x03);

    sendOrder(0xC0); // ST7735R Power Sequence
    sendByte(0x28);
    sendByte(0x08);
    sendByte(0x04);

    sendOrder(0xC1);
    sendByte(0XC0);

    sendOrder(0xC2);
    sendByte(0x0D);
    sendByte(0x00);
    sendOrder(0xC3);

    sendByte(0x8D);
    sendByte(0x2A);

    sendOrder(0xC4);
    sendByte(0x8D);
    sendByte(0xEE);
    //---------------------------------End ST7735S Power Sequence-------------------------------------//
    sendOrder(0xC5); //VCOM
    sendByte(0x1A);
    sendOrder(0x36); //MX, MY, RGB mode
    if (LCD_DIR == 1) sendByte(0xC0);  // 重要：显示方向控制，C0/00/A0/60,  C8/08/A8/68
    if (LCD_DIR == 2) sendByte(0x00);
    if (LCD_DIR == 3) sendByte(0xA0);
    if (LCD_DIR == 4) sendByte(0x60);
    //------------------------------------ST7735S Gamma Sequence-----------------------------------------//
    sendOrder(0xE0);
    sendByte(0x04);
    sendByte(0x22);
    sendByte(0x07);
    sendByte(0x0A);
    sendByte(0x2E);
    sendByte(0x30);
    sendByte(0x25);
    sendByte(0x2A);
    sendByte(0x28);
    sendByte(0x26);
    sendByte(0x2E);
    sendByte(0x3A);
    sendByte(0x00);
    sendByte(0x01);
    sendByte(0x03);
    sendByte(0x13);

    sendOrder(0xE1);
    sendByte(0x04);
    sendByte(0x16);
    sendByte(0x06);
    sendByte(0x0D);
    sendByte(0x2D);
    sendByte(0x26);
    sendByte(0x23);
    sendByte(0x27);
    sendByte(0x27);
    sendByte(0x25);
    sendByte(0x2D);
    sendByte(0x3B);
    sendByte(0x00);
    sendByte(0x01);
    sendByte(0x04);
    sendByte(0x13);

    // 后期复制增加的，不明白
    sendOrder(0x2a);
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x7f);
    // 后期复制增加的，不明白
    sendOrder(0x2b);
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x9f);
    //------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
    sendOrder(0x3A); // 65k mode
    sendByte(0x05);

    sendOrder(0x29); // Display on

    LCD_Fill(1, 1, xLCD.width, xLCD.height, BLACK);
    xLCD.InitOK = 1;
}

// 向LCD发送寄存器地址(指令)
void sendOrder(u16 order) {
    LCD_CS_LOW;            // SPI设备片选拉低，开始通信
    LCD_RS_LOW;            // RS高: 数据值， RS低: 寄存器地址值
    spiSendByte(order);    // 发送 寄存器地址值
    LCD_CS_HIGH;           // SPI设备片选拉高，结束通信
}

// 向LCD发送数值
void sendByte(u8 data) {
    LCD_CS_LOW;            // SPI设备片选拉低，开始通信
    LCD_RS_HIGH;           // RS高: 数据值， RS低: 寄存器地址值
    spiSendByte(data);     // 发送1字节
    LCD_CS_HIGH;           // SPI设备片选拉高，结束通信
}

// 向LCD发送2个字节
void sendShort(u16 data) {
    LCD_CS_LOW;            // SPI设备片选拉低，开始通信
    LCD_RS_HIGH;           // RS高: 数据， RS低: 指令
    spiSendByte(data >> 8);  // 发送1字节
    spiSendByte(data);     // 发送1字节
    LCD_CS_HIGH;           // SPI设备片选拉高，结束通信
}

//写寄存器: 寄存器地址，数据
void sendRegisterValue(u8 reg, u16 val) {
    sendOrder(reg);
    sendShort(val);
}

/*****************************************************************
 * 函  数：LCD_Display
 * 功  能：显示屏开关
 * 参  数：0:熄，非0：开
 * 返回值：无
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void LCD_Display(u8 sw) {
    if (sw == 0)
        LCD_BL_LOW;
    else
        LCD_BL_HIGH;
}

/*****************************************************************
 * 函  数：setCursor
 * 功  能：设置显示区域，在此区域写点数据自动换行
 * 参  数：xy起点和终点
 * 返回值：无
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
******************************************************************/
void setCursor(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd) {
    sendOrder(0x2A);
    sendByte(xStart >> 8);   // 起始位置x高位，因为1.8寸屏是128*160, 不大于255, 直接写0省事
    sendByte(xStart); // 起始位置x低位，值传递时自动舍弃了高8位，也省得运算了
    sendByte(xEnd >> 8);   // 起始位置y高位
    sendByte(xEnd);   // 起始位置x位位

    sendOrder(0x2B);
    sendByte(yStart >> 8);
    sendByte(yStart);
    sendByte(yEnd >> 8);
    sendByte(yEnd);

    sendOrder(0x2c);  // 发送写数据命令
}

/*************************************************
函数名：在rawPoint
功  能：画一个点
参  数：无
返回值：无
*************************************************/
void drawPoint(u16 x, u16 y, u16 color) {
    if (map[x][y] != color) {
        map[x][y] = color;
        setCursor(x, y, x, y);      //设置光标位置
        sendShort(color);
    }
}

/******************************************************************
 * 函数名： LCD_Fill
 * 功  能： 在指定区域内填充单个颜色
 *          屏幕坐标从1开始；屏幕左右和下方实际上有多余行列
 * 参  数： u16 xStart, yStart  左上角起始坐标
 *          u16 xEnd,   yEnd    右下角起始坐标
 *          u32 Color           填充的颜色
 *
 * 备  注： 魔女开发板团队编写   淘宝 https://demoboard.taobao.com
 * 分  享： 不断更新于Q群文件夹：262901124  最后修改_2020年09月01日
 *****************************************************************/
void LCD_Fill(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color) {
//    spiInit();                                      // 防止SPI参数被其它设备修改了
    u32 pixel = (xEnd - xStart + 1) * (yEnd - yStart + 1);    // 填充的像素数量

    setCursor(xStart, yStart, xEnd, yEnd);        // 设定填充范围
    while (pixel-- > 0)                                // 发送颜色值
        sendShort(color);
}

/******************************************************************
 * 函数名： LCD_Line
 * 功  能： 画线
 * 参  数： u16 x1,y1  起点坐标
 *          u16 x2,y2  终点坐标
 *          u32 Color  颜色
 *****************************************************************/
void LCD_Line(u16 sX, u16 sY, u16 eX, u16 eY, u16 color) {
//    spiInit();                                      // 防止SPI参数被其它设备修改了

    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = eX - sX; //计算坐标增量
    delta_y = eY - sY;
    uRow = sX;
    uCol = sY;
    if (delta_x > 0)incx = 1; //设置单步方向
    else if (delta_x == 0)incx = 0;//垂直线
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0;//水平线
    else {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x; //选取基本增量坐标轴
    else distance = delta_y;
    for (t = 0; t <= distance + 1; t++)//画线输出
    {
        drawPoint(uRow, uCol, color);//画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
// 原厂商提供的画圆函数，感觉有点失真，后面再慢慢搞它吧
void LCD_Circle(u16 x0, u16 y0, u8 r, u16 color) {
//    spiInit();                                   // 防止SPI参数被其它设备修改了
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);                                 //判断下个点位置的标志
    while (a <= b) {
        drawPoint(x0 + a, y0 - b, color);             //5
        drawPoint(x0 + b, y0 - a, color);             //0
        drawPoint(x0 + b, y0 + a, color);             //4
        drawPoint(x0 + a, y0 + b, color);             //6
        drawPoint(x0 - a, y0 + b, color);             //1
        drawPoint(x0 - b, y0 + a, color);
        drawPoint(x0 - a, y0 - b, color);             //2
        drawPoint(x0 - b, y0 - a, color);             //7
        a++;
        //使用Bresenham算法画圆
        if (di < 0)di += 4 * a + 6;
        else {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

/******************************************************************
 * 函数名： LCD_Image
 * 功  能： 在指定区域内填充指定图片数据
 *          图片数据在font.h文件中.只适合少量图片保存
 *          Image2Lcd转换：水平扫描，16位真彩色
 * 参  数： u16 x,y     左上角起始坐标
 *          u16 width   图片宽度
 *          u16 height  图片高度
 *          u8* image   数据缓存地址
 * 备  注： 魔女开发板团队  资料存放Q群：262901124        最后修改_2020年09月2日
 *****************************************************************/
void LCD_Image(u16 x, u16 y, u16 width, u16 height, const u8 *image) {
//    spiInit();                                 // 防止SPI参数被其它设备修改了

    u16 colorData = 0;
    u32 cnt = 0;

    for (u16 i = 0; i < height; i++)                // 一行一行地显示
    {
        setCursor(x, y + i, x + width, y + height);  // 重新设置光标位置
        for (u16 j = 0; j < width; j++)             // 一行中，从左到事，逐个像素处理
        {
            colorData = (image[cnt * 2 + 1] << 8) | image[cnt * 2];
            sendShort(colorData);              // 写入16位颜色数据
            cnt++;
        }
    }
}

/******************************************************************
 * 函数名： LCD_Chinese16ForFile
 * 功  能： 显示1个16号汉字,字库数据在font文件中，只适合少量汉字固定输出
 *          PCtoLCD2002取模：阴码+逐列式+顺向+C51格式
 * 参  数： u16 x,y     左上角起始坐标
 *          u8  index   字库数据在缓存中的位置
 *          u32 fColor  字色
 *          u32 bColor  底色
 *****************************************************************/
void LCD_Chinese(u32 x, u32 y, u8 index, uint8_t size, u16 fColor, u16 bColor) {
//    spiInit();                                      // 防止SPI参数被其它设备修改了

    const u8 *temp = bitmap_bytes[index];              // 获取字体数据在数组中的的起始位置
    const u8 len = bitmap_bytes_len[index];
    for (u8 j = 0; j < size; j++) {
        setCursor(x, y + j, x + size * len, y + j + size);
        for (int c = 0; c < len; c++) {
            for (u8 k = 0; k < size >> 3; k++) {
                for (u8 i = 0; i < 8; i++) {
                    if ((*temp & (128 >> i)) != 0)
                        sendShort(fColor);
                    else
                        sendShort(bColor);
                }
                temp++;
            }
        }
    }
}

/******************************************************************
 * 函数名： LCD_Chinese32ForFile
 * 功  能： 显示1个32号汉字,字库数据在font文件中，只适合少量汉字固定输出
 *          PCtoLCD2002取模：阴码+逐列式+顺向+C51格式
 * 参  数： u16 x,y     左上角起始坐标
 *          u8  index   字库数据在缓存中的位置
 *          u32 fColor  字体颜色
 *          u32 bColor  背景颜色
 *****************************************************************/
//void LCD_Chinese32ForFile(u32 x, u32 y, u8 index, u16 fColor, u16 bColor) {
////    spiInit();                                  // 防止SPI参数被其它设备修改了
//
//    const u8 *temp = hanzi32 + index * 128;       // 获取字体数据在数组中的的起始位置
//
//    for (u8 j = 0; j < 32; j++)                      // 一行一行地向下写
//    {
//        setCursor(x, y + j, x + 32, y + j + 32);          // 只要定位了首个坐标，后面发送的数据，就会向后排列，直至收到新的命令
//        for (u8 k = 0; k < 4; k++) {
//            for (u8 i = 0; i < 8; i++) {
//                if ((*temp & (1 << i)) != 0)
//                    sendShort(fColor);
//                else
//                    sendShort(bColor);
//            }
//            temp++;
//        }
//    }
//}

/******************************************************************
 * 函数名： drawAscii
 * 功  能： 在指定位置显示一个字符
 * 参  数： u16 x,y     起始坐标
 *          u8  num     要显示的字符:" "--->"~"
 *          u8  size    字体大小 12/16/24/32
 *          u32 fColor  字体颜色
 *          u32 bColor  背景颜色
 * 备  注： 参考原子哥和野火大神的代码后修改  资料存放Q群：262901124
 *****************************************************************/
void drawAscii(u16 x, u16 y, u8 num, u8 size, u32 fColor, u32 bColor) {
//    spiInit();                                        // 防止SPI参数被其它设备修改了

    if (xLCD.InitOK == 0) return;

    u8 temp;
    u16 y0 = y;

    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);           // 得到字体一个字符对应点阵集所占的字节数
    num = num - ' ';                                       // 得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
    for (u8 t = 0; t < csize; t++) {
        if (size == 12) temp = asc2_1206[num][t];   // 调用1206字体
        else if (size == 16) temp = asc2_1608[num][t];   // 调用1608字体
        else if (size == 24) temp = asc2_2412[num][t];   // 调用2412字体
        else if (size == 32) temp = asc2_3216[num][t];   // 调用3216字体
        else return;                                   // 没有的字库

        for (u8 t1 = 0; t1 < 8; t1++) {
            if (temp & 0x80) {
                drawPoint(x, y, fColor);  // 字体 画点
            } else {
                drawPoint(x, y, bColor);
            } // 背景 画点
            temp <<= 1;
            y++;
            if (y >= xLCD.height) return;               // 超出屏幕高度(底)
            if ((y - y0) == size) {
                y = y0;
                x++;
                if (x >= xLCD.width) return;              // 超出屏幕宽度(宽)
                break;
            }
        }
    }
}

/*
// code 字符指针开始
// 从字库中查找出字模
// code 字符串的开始地址,GBK码
// mat  数据存放地址 (size/8+((size%8)?1:0))*(size) bytes大小
// size:字体大小
void GetGBK(u8 *code, u8 *mat, u8 size) {
    u8 qh, ql;
    u32 foffset;
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size);    // 计算汉字点阵大小，单位字节数

    qh = *code;
    ql = *(++code);

    if (qh < 0x81 || ql < 0x40 || ql == 0xff || qh == 0xff)    // 非常用汉字，将用填充显示整个位置
    {
        for (u8 i = 0; i < csize; i++) *mat++ = 0x00;  // 填充满格
        return;                                 // 结束访问
    }

    if (ql < 0x7f)ql -= 0x40;                        // 计算要提取的汉字在字库中的偏移位置
    else ql -= 0x41;
    qh -= 0x81;
    foffset = ((unsigned long) 190 * qh + ql) * csize;    // 得到汉字在字库中的偏移位置

    switch (size) {                                                                                 // 按字体的不同，在不同字库读取字体点阵
        case 12:
            W25qxx_ReadBuffer(foffset + GBK_STORAGE_ADDR, mat, csize);    // 12号字体
            break;
        case 16:
            W25qxx_ReadBuffer(foffset + GBK_STORAGE_ADDR + 0x0008c460, mat, csize);    // 12号字体
            break;
        case 24:
            W25qxx_ReadBuffer(foffset + GBK_STORAGE_ADDR + 0x001474E0, mat, csize);    // 24号字体
            break;
        case 32:
            W25qxx_ReadBuffer(foffset + GBK_STORAGE_ADDR + 0x002EC200, mat, csize);    // 32号字体
            break;
    }
}

// 显示汉字
void drawGBK(u16 x, u16 y, u8 *font, u8 size, u32 fColor, u32 bColor) {
    u8 temp;
    u16 y0 = y;
    u8 GBK[128];
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size);    // 得到字体一个字符对应点阵集所占的字节数
    GetGBK(font, GBK, size);                    // 得到相应大小的点阵数据

    spiInit();                                  // 防止SPI参数被其它设备修改了
    for (u8 t = 0; t < csize; t++) {
        temp = GBK[t];                            // 得到GBK点阵数据
        for (u8 t1 = 0; t1 < 8; t1++) {
            if (temp & 0x80) drawPoint(x, y, fColor);
            else drawPoint(x, y, bColor);
            temp <<= 1;
            y++;
            if ((y - y0) == size) {
                y = y0;
                x++;
                break;
            }
        }
    }
}
 */

/******************************************************************************
 * 函  数： LCD_String
 * 功  能： 在屏幕上显示字符串，支持英文、中文
            重要提示：注意字库的格式、位置， 本函数字库在W25Q128中
 *
 * 参  数：
 * 返回值：　
 * 备  注： 魔女开发板团队  资料存放Q群：262901124        最后修改_2020年05月1８日
 ******************************************************************************/
void LCD_String(u16 x, u16 y, char *pFont, u8 size, u32 fColor, u32 bColor) {
    if (xLCD.InitOK == 0)
        return;

    u16 xStart = x;

    // 字体大小控制
    if (size != 12 && size != 16 && size != 24 && size != 32)
        size = 24;

    while (*pFont != 0) {
        // 位置控制
        if (x > (xLCD.width - size))       // 如果这一行不够位置，就下一行
        {
            x = xStart;
            y = y + size;
        }
        if (y > (xLCD.height - size))    // 如果到了屏幕底部，就返回，不再输出
            return;

        // 判断文字是ASCII还是汉字
        if (*pFont < 127)              // ASCII字符
        {
            drawAscii(x, y, *pFont, size, fColor, bColor);
            pFont++;
            x += size / 2;
        } else                          // 汉字显示
        {
            // 重要: 如果用的不是魔女开发板的字库, 就要修改或注释下面这一行, 这样就不影响ASCII英文字符的输出
            // drawGBK(x, y, (u8 *) pFont, size, fColor, bColor);
            pFont = pFont + 2;          // 下一个要显示的数据在内存中的位置
            x = x + size;                 // 下一个要显示的数据在屏幕上的X位置
        }
    }
}

void mLCD_String(u16 x, u16 y, char *pFont, u8 size, u32 fColor, u32 bColor) {
    if (xLCD.InitOK == 0)
        return;
    // 字体大小控制
    if (size != 12 && size != 16 && size != 24 && size != 32)
        size = 24;

    u16 xStart = x;
    u16 yStart = y;
    u16 xEnd = x + size;
    u16 yEnd = y + size;
    while (*pFont != 0) {
        // 位置控制
        if (x > (xLCD.width - size))       // 如果这一行不够位置，就下一行
        {
            x = xStart;
            y = y + size;
        }
        if (y > (xLCD.height - size))    // 如果到了屏幕底部，就返回，不再输出
            return;

        // 判断文字是ASCII还是汉字
        if (*pFont < 127)              // ASCII字符
        {
            if (xLCD.InitOK == 0) return;

            u8 temp;
            u16 y0 = y;

            u8 num = *pFont;
            u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);           // 得到字体一个字符对应点阵集所占的字节数
            num = num - ' ';                                       // 得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
            for (u8 t = 0; t < csize; t++) {
                if (size == 12) temp = asc2_1206[num][t];   // 调用1206字体
                else if (size == 16) temp = asc2_1608[num][t];   // 调用1608字体
                else if (size == 24) temp = asc2_2412[num][t];   // 调用2412字体
                else if (size == 32) temp = asc2_3216[num][t];   // 调用3216字体
                else return;                                   // 没有的字库

                for (u8 t1 = 0; t1 < 8; t1++) {
                    if (temp & 0x80) {
                        map[x][y] = fColor;
                    } else {
                        map[x][y] = bColor;
                    } // 背景 画点
                    temp <<= 1;
                    y++;
                    if (y >= xLCD.height) return;               // 超出屏幕高度(底)
                    if ((y - y0) == size) {
                        y = y0;
                        x++;
                        if (x >= xLCD.width) return;              // 超出屏幕宽度(宽)
                        break;
                    }
                }
            }
            pFont++;
            x += size / 2;
        } else                          // 汉字显示
        {
            // 重要: 如果用的不是魔女开发板的字库, 就要修改或注释下面这一行, 这样就不影响ASCII英文字符的输出
            // drawGBK(x, y, (u8 *) pFont, size, fColor, bColor);
            pFont = pFont + 2;          // 下一个要显示的数据在内存中的位置
            x = x + size;                 // 下一个要显示的数据在屏幕上的X位置
        }
    }

    setCursor(xStart, yStart, xEnd, yEnd);
    for (int i = xStart; i < xEnd; i++) {
        for(int j = yStart; j < yEnd; j++) {
            sendShort(map[i][j]);
        }
    }
}
