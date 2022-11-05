#define  DEFINES_LM3S1968
#include "Defines.h"
#include "delay.h"
#include "CM3_PWM.h"



void PWM2_Init(unsigned short periodo, unsigned short ciclo_util_A, unsigned short ciclo_util_B)
{

  SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM;   // Habilita el reloj del modulo PWM
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // Habilita el reloj del puerto
	delay(2000); // Retardo para estabilizar registros
	
	GPIO_PORTF_AFSEL_R|= 	0xC;
	GPIO_PORTF_DIR_R 	|=  0xC;					 //CONFIGURACION DEL PUERTO COMO SALIDA DE DATOS
  GPIO_PORTF_DEN_R 	|=	0xC;					 //habilitar los datos digitales en los dos primeros pines del puerto F
	
	
	SYSCTL_RCC_R 			&= ~SYSCTL_RCC_PWMDIV_M;
	SYSCTL_RCC_R 			|=(SYSCTL_RCC_USEPWMDIV|SYSCTL_RCC_PWMDIV_2);

	PWM_2_CTL_R 			 = 0;
	PWM_2_GENA_R			 = PWM_X_GENA_ACTCMPAU_ZERO | PWM_X_GENA_ACTZERO_ONE;
	PWM_2_GENB_R			 = PWM_X_GENB_ACTCMPBU_ZERO | PWM_X_GENB_ACTZERO_ONE;
	
	PWM_2_LOAD_R			 =	periodo - 1;
	PWM_2_CMPA_R			 =	ciclo_util_A - 1;
	PWM_2_CMPB_R			 =	ciclo_util_B - 1;
	PWM_2_CTL_R				|=	PWM_X_CTL_MODE | PWM_X_CTL_ENABLE;
}
// change duty cycle
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void PWM2_Duty_A(unsigned short ciclo_util_A)
{
	PWM_2_CMPA_R 	 			= ciclo_util_A - 1; 
}

void PWM2_Duty_B(unsigned short ciclo_util_B)
{
  PWM_2_CMPB_R 			 = ciclo_util_B - 1; 
}

void PWM2_ENABLE_A(void)
{
	PWM_ENABLE_R			|=	PWM_ENABLE_PWM4EN;		
}
void PWM2_ENABLE_B(void)
{
	PWM_ENABLE_R			|=	PWM_ENABLE_PWM5EN;		
}

void PWM2_DISABLE_A(void)
{
	PWM_ENABLE_R			&=	~PWM_ENABLE_PWM4EN;	
}

void PWM2_DISABLE_B(void)
{
	PWM_ENABLE_R			&=	~PWM_ENABLE_PWM5EN;		
}

