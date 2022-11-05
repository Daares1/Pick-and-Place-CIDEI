#include "varios.h"
#include "Defines.h"
#include "Delay.h"
/**************************************************************************************
Funcion: Init_MCU
**************************************************************************************/

char Init_MCU (void)
{
	SYSCTL_RCC_R =	~	(SYSCTL_RCC_BYPASS				//	 Bypass=Off
					|	SYSCTL_RCC_ACG	    			//	 Acg=Off
					|	SYSCTL_RCC_PWRDN				//   PWRDN=off
					)
         			&
					(	SYSCTL_RCC_SYSDIV_8			    //	 Divisor de reloj de sistema SYSCTL_RCC_SYSDIV_x (200000000/x)
					|	SYSCTL_RCC_USESYSDIV			//	 Habilite el divisor de reloj de sistema=On
					|	SYSCTL_RCC_XTAL_8MHZ			//   Reloj de sistema Cristal 8Mhz
					);
	SYSCTL_RCGC1_R = (SYSCTL_RCGC1_TIMER0 | SYSCTL_RCGC1_TIMER1 | SYSCTL_RCGC1_TIMER2 | SYSCTL_RCGC1_TIMER3);

delay(20);
return 1;
}//End void Init_MCU (void)

/*************************************************************************************/

