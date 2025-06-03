#include "stm32f10x.h"
#include "led.h"
#include "serial.h" //����ͨ��
#include "delay.h" //��ʱ����
#include "oled.h" // OLED��ʾ����
#include "usart2.h" //����2 ����
#include "gizwits_product.h" // ������������ƽ̨
#include "gizwits_protocol.h" // ������Э��
#include "timer.h"  // ��ʱ��
#include "dht11.h" // ��ʪ�ȴ�����
#include "AD.h" // ģ��ת��������/MQ135��

/*********************************************����Ŀ������������Դ��@Bվ ��Э�Ƽ���@Bվ ���絥Ƭ�����**********************************************/

/*********************************************����Ŀ��Դ������ֹ׬����Ǯ��������Bվ������Eֻ�����**************************************************/
/*
���ֹ��ܻ����Լ�����չ������˵�������Ƽ�ʪ�������ȵȵ�
�Լ����������ƵĹ��ȷ�װ��ʹ��MQTTЭ�飬������Ŀ������Ҳ���Եõ�����
�ܵ���˵������Ŀ���ʺ�С���������֣����кܴ�������ռ�
*/
/*********************************************����Ŀ��Դ������ֹ׬����Ǯ��������Bվ������Eֻ�����**************************************************/
u8 temp; // �¶�
u8 humi; // ʪ��
u8 DHT_Buffer[5]; // �洢 DHT11 �ɼ�������
uint8_t RxData;			         //�������ڽ��մ������ݵı���
uint8_t Serial_RxData;		//���崮�ڽ��յ����ݱ���
uint8_t Serial_RxFlag;		//���崮�ڽ��յı�־λ����
int main(void)
{ 
		// �ֶ���ʼ�� DHT11 �����ݣ�����OLED��ʾ�Ĺ����ṩ��ģ������
    DHT_Buffer[0]=71;
    DHT_Buffer[3]=0;
		DHT_Buffer[2]=14;
    DHT_Buffer[3]=37;
		
	
    SystemInit();//����ϵͳʱ��Ϊ72M	
		delay_init(72); // ϵͳʱ��Ƶ��Ϊ72MHZ
		LED_Init(); // ��ʼ��LED��GPIO���ã����ö�Ӧ������Ϊ���ģʽ (PA6)
		Serial_Init();//���ڳ�ʼ�� ������1��
		USART2_Config();//���ڳ�ʼ��  ������2��
    AD_Init(); // ģ��ת��
		TIM3_Int_Init(1000-1,72-1);		//��ʱ1ms�ж�   Ϊ�������ṩ����
		OLED_Init(); // ��ʼ�� OLED ��ʾ��
		delay_ms(1000);
	
		// OLED �Ĳ���
    OLED_ShowString(1,1,"Light:");
    OLED_ShowString(2,1,"Air_Quality:");     
    OLED_ShowString(1, 9, "%");
    OLED_ShowString(2, 15, "%");
    OLED_ShowString(3,1,"Humi");
    OLED_ShowString(3,8,"Temp");
    OLED_ShowString(3,14,".");
		
	userInit(); // ��ʼ�����豸��ص��������ݵ������ȷ��������ϵͳ����ʱ���ڰ�ȫ��ȷ���ĳ�ʼ״̬
	gizwitsInit(); // ��ʼ��������Э��ջ��׼��ͨ�ţ�gizwitsInit��
	delay_ms(500); // ��ʱ500���룬ȷ��ģ���ȶ�
	gizwitsSetMode(WIFI_AIRLINK_MODE); // ���û�����ΪAirLink����ģʽ��ʹ�豸�ܹ������ֻ�APP���͵�Wi-Fi��Ϣ�������������
    while (1)
    {
        
	if(DHT_Get_Temp_Humi_Data(DHT_Buffer)) // ��ȡ���ݳɹ�
        {   
						// ��OLED ��ʾ����
            OLED_ShowNum(3,5,DHT_Buffer[0],2);		
            OLED_ShowNum(3,12,DHT_Buffer[2],2);
            OLED_ShowNum(3,15,DHT_Buffer[3],2);								
        }             
        
    OLED_ShowNum(1,7,100-Get_Light_Percentage_value(),2);
    OLED_ShowNum(2,13,100-Get_MQ135_Percentage_value(),2);
				
		// ʵʱ�ɼ����������ݲ�����Ԥ�������µ����������ݵ�ṹ����
    userHandle(); 
		
		// �������������ƽ̨����˫��ͨ�ŵĺ��Ľӿ�
    gizwitsHandle((dataPoint_t *)&currentDataPoint);
		
  }
}
/*-----------------------------------------------------------------------�����жϷ�����--------------------------------------------------------------------------*/
// ����ͨ�����ڽ��յ������ݲ����ݲ�ָͬ�����Ӳ���豸
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{
		Serial_RxData = USART_ReceiveData(USART1);				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		Serial_RxFlag = 1;										    //�ý��ձ�־λ����Ϊ1
        
        /*���USART1��RXNE��־λ ��ȡ���ݼĴ������Զ�����˱�־λ ����Ѿ���ȡ�����ݼĴ�����Ҳ���Բ�ִ�д˴���*/  
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
  	    RxData = Serial_GetRxData();		                        //��ȡ���ڽ��յ�����
        if(RxData==0x03)                                           //���ж�10���Ƶ�,��16���Ƶ�
        {
            LED_On();
        }
        if(RxData==0x04)
        {
            LED_Off();
        }
        if(RxData==0x05)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_7);  
        }
        if(RxData==0x06)
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_7);  
        }
        if(RxData==0x07)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_6);  
        }
        if(RxData==0x08)
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_6);  
        }
	}
}
