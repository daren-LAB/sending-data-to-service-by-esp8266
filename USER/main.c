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
	unsigned short timeCount = 0;	//发送间隔变量
	unsigned char *dataPtr = NULL;

	u16 times=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	uart3_init(115200);
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	
		ESP8266_Init();	
		while(OneNet_DevLink())			//接入OneNET
	  delay_ms(500);
		
		OneNet_Subscribe(topics, 1);

 	while(1)
	{

		if(++timeCount >= 100)									//发送间隔5s
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
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		
	}	 
 }

