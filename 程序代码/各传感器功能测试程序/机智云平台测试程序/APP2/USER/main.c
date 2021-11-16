/*
1.项目名称：绿深旗舰店-STM32综合测试板指纹模块测试程序
2.显示模块：0.96寸绿深OLED屏
3.配套APP：无
4.配套上位机：无
5.项目组成：0.96寸绿深OLED屏、AS608指纹模块、绿深STM32综合测试板
6.项目功能：添加、删除、验证指纹。具体操作请看演示视频
7.主要原理：具体参考AS608指纹模块数据手册
8.购买地址：https://lssz.tmall.com 或淘宝上搜索“绿深旗舰店”
9.演示视频：宝贝详情页面或购买后像客服索要！
10.版权声明：绿深旗舰店所有程序都申请软件著作权。均与本店产品配套出售，请不要传播，以免追究其法律责任！
*/
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "key.h"
#include "timer.h"
#include "usart3.h"
#include "usart.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"
#include "rx_data_queue.h"
#include "bsp_usart2.h"

dataPoint_t currentDataPoint;
extern char redata[100];
extern u8 wifi_flag;

char temp[4],humi[4];
char pm[6];
char light[7];
int tempvalue,humivalue;
float dustvalue,lightvalue;




void Gizetis_Init()
{
	TIM3_Int_Init(9,7199);
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}

void userHandle(void)
{
	if(wifi_flag == 1)
	{
		currentDataPoint.valuetemp = tempvalue;
		currentDataPoint.valuehumi = humivalue;
		currentDataPoint.valuedust = dustvalue;
		currentDataPoint.valuelight = lightvalue;
	}
}


int main(void)
{		
	int key_num;

	USART2_Config();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();
	uart_init(115200);

	
	usart3_init(9600);
	rx_queue_init();
	KEY_Init();
	Gizetis_Init();
	printf("初始化完成\r\n");
	while(1)
	{		
		
		pull_data_from_queue();
		Extraction_str(redata,temp,humi,pm,light);
		tempvalue=atoi(temp);
		humivalue=atoi(humi);
		dustvalue=atof(pm);
		lightvalue=atof(light);
		
		
		key_num=KEY_Scan(0);
		if(key_num==5)
		{
			key_num=0;
			__disable_irq();
	//		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	
			gizwitsSetMode(WIFI_AIRLINK_MODE);  //配网
			//gizwitsSetMode(WIFI_SOFTAP_MODE);    
			printf("配网完成\r\n");
			__enable_irq();
	//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
		}
		userHandle();
		
		gizwitsHandle((dataPoint_t *)&currentDataPoint); //协议处理
	}
}


