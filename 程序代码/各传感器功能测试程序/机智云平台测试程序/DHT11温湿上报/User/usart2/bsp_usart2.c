#include "bsp_usart2.h"
#include "gizwits_protocol.h"
#include "rx_data_queue.h"
// ��ʼ������2,��ZigBeeģ�����ͨ��
	


 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// �򿪴��������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = 115200;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USART2, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
	USART_ITConfig ( USART2, USART_IT_IDLE, ENABLE ); //ʹ�ܴ������߿����ж�
	// ʹ�ܴ���
	USART_Cmd(USART2, ENABLE);	    
}

void USART2_IRQHandler(void)
{
 uint8_t ucCh;
	QUEUE_DATA_TYPE *data_p; 
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{	
		ucCh  = USART_ReceiveData(USART3);
		//USART_SendData(USART3,ucCh);
						/*��ȡд������ָ�룬׼��д��������*/
		data_p = cbWrite(&rx_queue); 
		
		if (data_p != NULL)	//���������δ������ʼ����
		{		

			//��������д�����ݣ���ʹ�ô��ڽ��ա�dmaд��ȷ�ʽ
			*(data_p->head + data_p->len) = ucCh;
				
			if( ++data_p->len >= QUEUE_NODE_DATA_LEN)
			{
				cbWriteFinish(&rx_queue);
			}
		}else return;	
	}
	
	if ( USART_GetITStatus( USART2, USART_IT_IDLE ) == SET )                                         //����֡�������
	{
			/*д�뻺�������*/
			cbWriteFinish(&rx_queue);
		ucCh = USART_ReceiveData( USART2 );                                                              //�������������жϱ�־λ(�ȶ�USART_SR��Ȼ���USART_DR)

	}   
}

void Extraction_str(char* str,char* e,char* h,char* p,char* g)
{
	int i=0;
	int j=0,t=0;
	while(str[i] != '\0')
	{
		if(t==0)
		{
			if(str[i]==',')
			{
				t++;
				e[j]='\0';
				j=0;
				i++;
			}
			else
			{
				e[j]=str[i];
				j++;
			}
		}
		
		if(t==1)
		{
			if(str[i]==',')
			{
				t++;
				h[j]='\0';
				j=0;
				i++;
			}
			else
			{
				h[j]=str[i];
				j++;
			}
		}
		
		if(t==2)
		{
			if(str[i]==',')
			{
				t++;
				p[j]='\0';
				j=0;
				i++;
			}
			else
			{
				p[j]=str[i];
				j++;
			}
		}
			
		if(t==3)
		{
			if(str[i]==',')
			{
				t++;
				g[j]='\0';
				j=0;
				i++;
			}
			else
			{
				g[j]=str[i];
				j++;
			}
		}
			
		i++;
	}
	
}




/*****************  ����һ���ַ� **********************/
//void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
//{
//	/* ����һ���ֽ����ݵ�USART */
//	USART_SendData(pUSARTx,ch);
//		
//	/* �ȴ��������ݼĴ���Ϊ�� */
//	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
//}

///*****************  �����ַ��� **********************/
//void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
//{
//	unsigned int k=0;
//  do 
//  {
//      Usart_SendByte( pUSARTx, *(str + k) );
//      k++;
//  } while(*(str + k)!='\0');
//  
//  /* �ȴ�������� */
//  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
//  {}
//}

///*****************  ����һ��16λ�� **********************/
//void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
//{
//	uint8_t temp_h, temp_l;
//	
//	/* ȡ���߰�λ */
//	temp_h = (ch&0XFF00)>>8;
//	/* ȡ���Ͱ�λ */
//	temp_l = ch&0XFF;
//	
//	/* ���͸߰�λ */
//	USART_SendData(pUSARTx,temp_h);	
//	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
//	
//	/* ���͵Ͱ�λ */
//	USART_SendData(pUSARTx,temp_l);	
//	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
//}


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
//int fputc(int ch, FILE *f)
//{
//		/* ����һ���ֽ����ݵ����� */
//		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
//		
//		/* �ȴ�������� */
//		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
//	
//		return (ch);
//}

/////�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
//int fgetc(FILE *f)
//{
//		/* �ȴ������������� */
//		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

//		return (int)USART_ReceiveData(DEBUG_USARTx);
//}

