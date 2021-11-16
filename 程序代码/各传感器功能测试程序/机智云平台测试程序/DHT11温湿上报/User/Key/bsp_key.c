/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_key.h"  

//#include "sys.h"
/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
}



//mode:0,��֧����������1��֧��������

//u8 KEY_SCAN(u8 mode)
//{
//	static u8 key_up=1; //�������ɿ���־
//	if(mode) key_up=1;  //֧������
//	if(key_up&&(key1==0 || key2==0))
//	{
//		
//		delay_ms(10);
//		key_up=0;
//		if(key1==0) return 1;
//		else if(key2==0) return 2;
//	}else if(key1==1&&key2==1) key_up=1;
//	return 0;
//}

 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
uint8_t Key_Scan(void)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
		while(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON);   
		return 	1;	 
	}
	else if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
		while(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON);   
		return 	2;	 
	}
	else
		return 0;
}
/*********************************************END OF FILE**********************/
