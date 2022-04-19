#include  <string.h>
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "usart3.h"

#include "onenet.h"
#include "esp8266.h"

 int main(void)
 {		
	const char *topics[] = {"myfirst"};
	unsigned short timeCount = 0;	//���ͼ������
	unsigned char *dataPtr = NULL;

	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	uart3_init(115200);
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	
		ESP8266_Init();	
		while(OneNet_DevLink())			//����OneNET
	  delay_ms(500);
		
		OneNet_Subscribe(topics, 1);

 	while(1)
	{

		if(++timeCount >= 100)									//���ͼ��5s
		{
			printf("OneNet_Publish\r\n");		
			OneNet_Publish("pcTopic", "MQTT Publish Test");
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		
		
			times++;
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		
	}	 
 }

