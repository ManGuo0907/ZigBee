/**
  ******************************************************************************
  * @file    bsp_hc05.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   HC05����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� �Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "bsp_jdy.h"
#include "./usart/bsp_usart_blt.h"
#include <string.h>
#include <stdio.h>


 /**
  * @brief  ��ʼ��ģ����Ƶ�IO
  * @param  ��
  * @retval ��
  */
void JDY10M_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����GPIOʱ��*/
		RCC_APB2PeriphClockCmd( JDY_STAT_GPIO_CLK|JDY_PWRC_GPIO_CLK, ENABLE); 

		GPIO_InitStructure.GPIO_Pin = JDY_STAT_GPIO_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(JDY_STAT_GPIO_PORT, &GPIO_InitStructure);	
	
		
		GPIO_InitStructure.GPIO_Pin = JDY_PWRC_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(JDY_PWRC_GPIO_PORT, &GPIO_InitStructure);	

}



						   
	
 /**
  * @brief  ��JDYģ�鷢��������OK��ֻ�����ھ���OKӦ�������
	* @param  cmd:����������ַ�������Ҫ��\r\n��
	* @param	clean ����������Ƿ�������ջ�������1 �����0 �����
	* @template  ��λ���	JDY_Send_CMD("AT+RESET\r\n",1);	
  * @retval 0,���óɹ�;����,����ʧ��.	
  */
uint8_t JDY10M_Send_CMD(char* cmd,uint8_t clean)
{	

	
	uint8_t retry=5;
	uint8_t i,result=1;
	
	while(retry--)
	{
		JDY_PWRC_LOW;
		JDY_STAT_LOW;
		delay_ms(10);
		Usart_SendString(JDY10M_USART,(uint8_t *)cmd);
		
			for(i=0;i<20;i++)
			{ 
				uint16_t len;
				char * redata;
				
				delay_ms(10);
				
				redata = get_rebuff(&len); 
				if(len>0)
				{
					if(redata[0]!=0)
					{
						HC05_DEBUG("send CMD: %s",cmd);

						HC05_DEBUG("receive %s",redata);
					}
					if(strstr(redata,"OK"))				
					{
						
						if(clean==1)
							clean_rebuff();
						return 0;
					}
					else
					{
						//clean_rebuff();
					}
				}
				else
				{					
					delay_ms(100);
				}		
			}
			HC05_DEBUG("HC05 send CMD fail %d times",retry);
		}
	
	HC05_DEBUG("HC05 send CMD fail ");
		
	if(clean==1)
		clean_rebuff();

	return result ;

}

 /**
  * @brief  ʹ��͸���ַ�������
	* @param  str,Ҫ������ַ���
  * @retval ��
  */
void JDY10M_SendString(char* str)
{
//		BLT_KEY_LOW;
//	
//		Usart_SendString(HC05_USART,(uint8_t *)str);

}



 /**
  * @brief  ��ʼ��GPIO�����JDY10Mģ��
  * @param  ��
  * @retval JDY10M״̬��0 ��������0�쳣
  */
void JDY10M_Init(void)
{
	//uint8_t i;
	
	JDY10M_GPIO_Config();
	BLT_USART_Config();
	JDY_PWRC_LOW;
	JDY10M_Send_CMD( "AT+NETID123456789ABC\r\n",1);
	JDY10M_Send_CMD( "AT+NAME123\r\n",1);
	JDY10M_Send_CMD( "AT+RESET\r\n",1);

	JDY_PWRC_HIGHT;
}






 









