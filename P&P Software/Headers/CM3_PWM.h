#ifndef    Config_PWM_H
#define    Config_PWM_H

/***********************/


void PWM2_Init(unsigned short periodo, unsigned short ciclo_util_A, unsigned short ciclo_util_B);
void PWM2_Duty_A(unsigned short ciclo_util_A);
void PWM2_Duty_B(unsigned short ciclo_util_B);
void PWM2_ENABLE_A(void);
void PWM2_ENABLE_B(void);
void PWM2_DISABLE_A(void);
void PWM2_DISABLE_B(void);
/***********************/

#endif
