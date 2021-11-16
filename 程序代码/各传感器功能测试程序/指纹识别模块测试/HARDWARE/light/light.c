#include "light.h"
#include "delay.h"
#include "oled_iic.h"

typedef   unsigned char BYTE;
//BYTE    BUF[8];                         //接收数据缓存区   
//iic接口初始化


void Single_Write_BH1750(uchar REG_Address)
{
   IIC_Start();                  //起始信号
   Write_IIC_Byte(BHAddWrite);   //发送设备地址+写信号
   Write_IIC_Byte(REG_Address);    //内部寄存器地址，
  //  BH1750_SendByte(REG_data);       //内部寄存器数据，
   IIC_Stop();                   //发送停止信号
}

void Light_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* 打开GPIO时钟 */

//	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* 开漏输出 */
//	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

//	/* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
//	i2c_Stop();	

	Single_Write_BH1750(0x01);
	
	bh_data_send(BHPowOn);   
	bh_data_send(BHReset);   //16位AD转换，数值在1~65535(单位lx)
	bh_data_send(BHModeH2); //选择的是分辨率是0.5 lx，测量时间是120ms的
	delay_ms(180);
}


/*************************************************************************************/
void bh_data_send(u8 command)
{
    do{
    IIC_Start();                      //iic起始信号
    Write_IIC_Byte(BHAddWrite);       //发送器件地址
    }while(IIC_WaitAck());           //等待从机应答
    Write_IIC_Byte(command);          //发送指令
    IIC_WaitAck();                   //等待从机应答
    IIC_Stop();                       //iic停止信号
}

u16 bh_data_read(void)
{
	u16 buf;
	IIC_Start();                       //iic起始信号
	Write_IIC_Byte(BHAddRead);         //发送器件地址+读标志位
	IIC_WaitAck();                     //等待从机应答
	buf=i2c_ReadByte(); 
	i2c_Ack();	                    //读取数据
	buf=buf<<8;                        //读取并保存高八位数据
	buf+=0x00ff&i2c_ReadByte();      //读取并保存第八位数据
	i2c_NAck();
	IIC_Stop();                        //发送停止信号 
	return buf; 
}
