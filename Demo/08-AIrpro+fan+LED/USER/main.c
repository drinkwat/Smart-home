#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "Motor.h"
#include "key.h"
#include "dht11.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "timer.h"



u8 temp; // �¶�����
u8 humi; // ʪ������
u16 led0pwmval=0; // ̨�Ƶ�ռ�ձ�
extern u8 Res_1; // �������͵�ָ��

int main(void)
{ 
	u16 fan_speed = 100; // �����ٶ�

  SystemInit();//����ϵͳʱ��Ϊ72M	
	delay_init(72);
	LED_Init();
	LED_Off();
	MOTOR_Init();
	USART1_Config();// ��ʼ������1��������ģ��ͨ��
	USART2_Config();//   ��ʼ������2����ESP32ͨ��
	TIM1_Int_Init(1000-1,72-1);		//��ʱ1ms�жϣ�ΪЭ���ϵͳʱ�����ά��
	
	// �ȴ���ʪ�ȴ�������ʼ���ɹ�
	while(DHT11_Init())
	{
		printf("DHT11 Error \r\n");
	}
	
	OLED_Init();
	delay_ms(1000);
	
	OLED_Clear();

	//��ʾ���¶ȣ���
	OLED_ShowChinese(1,1, 0);
	OLED_ShowChinese(1,2, 1);
	OLED_ShowChar(1, 5, ':');
	OLED_ShowChar(1, 9, 'C');	
	//��ʾ��ʪ�ȣ���
	OLED_ShowChinese(2,1, 2);
	OLED_ShowChinese(2,2, 1);
	OLED_ShowChar(2, 5, ':');	
	OLED_ShowChar(2, 9, '%');
	
	// �����ݵ����㣬ȷ���豸����ʱ���������Ϳ���״̬����Ĭ��ֵ
	userInit();
	
	// ��ʼ��Э��ջ�ĺ�����������λ�������Э����ƿ飩��Ϊ�ƶ�ͨ����׼��
	// ��ʵ���Ǵ�����һ�����������������С
	gizwitsInit();
	delay_ms(500);
	
	// ��������������ģʽ
	// ���豸����Ϊ"AIRLINKģʽ"����������ģʽ��
	// �����û�ͨ���ֻ�APP��������ƹٷ�APP������APP�����ٽ��豸���ӵ���ͥ����ҵWiFi����
	gizwitsSetMode(WIFI_AIRLINK_MODE);

		while(1)
		{
			DHT11_Read_Data(&temp,&humi); // ��ȡ��ʪ�ȴ������ɼ�������
			userHandle();//���´����������ݵ���ǰ���ݵ�ṹ����
			
			// ���������ƶ˻�APP��Э�����ݰ�������ָ�������Ӧ����
			// �������ϴ����ƶ�
			gizwitsHandle((dataPoint_t *)&currentDataPoint);
			
			if (Res_1==02)
			{
				LED_Off();//�ط���
				Fan_SetSpeed(100);
			}

			else if(Res_1==01)
			{
					
				LED_On();//���ַ��ȴ򿪣�ʵ��ûɶ����
				
			}
			
			else if(Res_1==03)
			{
					
				Fan_SetSpeed(40);//��һ��
			}
			
			else if(Res_1==04)
			{
					
				Fan_SetSpeed(0);//�ڶ���
			}
			else if(Res_1==05)
			{
					
				Fan_SetSpeed(0);//����ģʽ
			}

				
			

			
			LED_SetBrightness(led0pwmval);	// ����̨��	

			//��ʾ�¶�����
		OLED_ShowNum(1,6,temp,2);
		//��ʾʪ������
		OLED_ShowNum(2,6,humi,2);
  }
}


