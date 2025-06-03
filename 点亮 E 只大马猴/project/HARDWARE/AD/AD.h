#ifndef __AD_H
#define __AD_H

extern uint16_t AD_Value[4];

void AD_Init(void);
uint8_t Get_MQ135_Percentage_value(void);
uint8_t Get_Light_Percentage_value(void);

#endif
