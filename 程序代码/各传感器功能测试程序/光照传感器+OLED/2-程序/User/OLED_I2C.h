#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

#include "stm32f10x.h"
#include <inttypes.h>

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

#define GPIO_PORT_I2C	 GPIOC			/* GPIO端口 */
#define RCC_I2C_PORT 	 RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define I2C_SCL_PIN		 GPIO_Pin_6			/* 连接到SCL时钟线的GPIO */
#define I2C_SDA_PIN		 GPIO_Pin_7			/* 连接到SDA数据线的GPIO */

extern unsigned int HZ;



/* 定义读写SCL和SDA的宏，已增加代码的可移植性和可阅读性 */
#if 1	/* 条件编译： 1 选择GPIO的库函数实现IO读写 */
	#define I2C_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 1 */
	#define I2C_SCL_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 0 */
	
	#define I2C_SDA_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 1 */
	#define I2C_SDA_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 0 */
	
	#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)	/* 读SDA口线状态 */
#else	/* 这个分支选择直接寄存器操作实现IO读写 */
    /*　注意：如下写法，在IAR最高级别优化时，会被编译器错误优化 */
	#define I2C_SCL_1()  GPIO_PORT_I2C->BSRR = I2C_SCL_PIN				/* SCL = 1 */
	#define I2C_SCL_0()  GPIO_PORT_I2C->BRR = I2C_SCL_PIN				/* SCL = 0 */
	
	#define I2C_SDA_1()  GPIO_PORT_I2C->BSRR = I2C_SDA_PIN				/* SDA = 1 */
	#define I2C_SDA_0()  GPIO_PORT_I2C->BRR = I2C_SDA_PIN				/* SDA = 0 */
	
	#define I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)	/* 读SDA口线状态 */
#endif

void i2c_Start(void);
void i2c_Stop(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_ReadByte(void);
//uint8_t i2c_CheckDevice(uint8_t _Address);
uint8_t i2c_WaitAck(void);
void I2C_Configuration(void);
void I2C_WriteByte(uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N,unsigned char ch[]);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_ShowFloat(unsigned char x, unsigned char y,float f, unsigned char TextSize);
void OLED_ShowInt(unsigned char x, unsigned char y,int f, unsigned char TextSize);

u32 oled_pow(u8 m, u8 n);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len,u8 mode);
void OLED_ShowChar(u8 x, u8 y, u8 chr);
void OLED_ShowCH(u8 x, u8 y,u8 *chs);
unsigned int GB16_NUM(void);
#endif
