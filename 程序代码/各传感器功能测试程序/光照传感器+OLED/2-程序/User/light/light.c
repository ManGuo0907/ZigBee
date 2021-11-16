#include "light.h"
#include "delay.h"
#include "OLED_I2C.h"

typedef   unsigned char BYTE;
//BYTE    BUF[8];                         //�������ݻ�����   
//iic�ӿڳ�ʼ��


void Single_Write_BH1750(uchar REG_Address)
{
   i2c_Start();                  //��ʼ�ź�
   I2C_WriteByte(BHAddWrite);   //�����豸��ַ+д�ź�
   I2C_WriteByte(REG_Address);    //�ڲ��Ĵ�����ַ��
  //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
   i2c_Stop();                   //����ֹͣ�ź�
}

void Light_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* ��GPIOʱ�� */

//	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* ��©��� */
//	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

//	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
//	i2c_Stop();	

	Single_Write_BH1750(0x01);
	
	bh_data_send(BHPowOn);   
	bh_data_send(BHReset);   //16λADת������ֵ��1~65535(��λlx)
	bh_data_send(BHModeH2); //ѡ����Ƿֱ�����0.5 lx������ʱ����120ms��
	DelayMs(180);
}


/*************************************************************************************/
void bh_data_send(u8 command)
{
    do{
    i2c_Start();                      //iic��ʼ�ź�
    I2C_WriteByte(BHAddWrite);       //����������ַ
    }while(i2c_WaitAck());           //�ȴ��ӻ�Ӧ��
    I2C_WriteByte(command);          //����ָ��
    i2c_WaitAck();                   //�ȴ��ӻ�Ӧ��
    i2c_Stop();                       //iicֹͣ�ź�
}

u16 bh_data_read(void)
{
	u16 buf;
	i2c_Start();                       //iic��ʼ�ź�
	I2C_WriteByte(BHAddRead);         //����������ַ+����־λ
	i2c_WaitAck();                     //�ȴ��ӻ�Ӧ��
	buf=i2c_ReadByte(); 
	i2c_Ack();	                    //��ȡ����
	buf=buf<<8;                        //��ȡ������߰�λ����
	buf+=0x00ff&i2c_ReadByte();      //��ȡ������ڰ�λ����
	i2c_NAck();
	i2c_Stop();                        //����ֹͣ�ź� 
	return buf; 
}
