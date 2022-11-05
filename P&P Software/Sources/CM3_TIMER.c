#include "varios.h"
#include "Defines.h"
#include "CM3_TIMER.h"
#include "Defines.h"
/**************************************************************************************
Funcion: Configurar_Timer0
**************************************************************************************/
int Config_Timer_0(float tim)
{
	int precarga0;
	precarga0 = (tim)*(FUc);
   
	TIMER0_CTL_R = !TIMER_CTL_TAEN;	 			//Modulo Timer deshabilitado.
	TIMER0_CFG_R = TIMER_CFG_32_BIT_TIMER;		//Contador en modo 32 bit.
	TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;		//Modulo en modo Timer.	
	TIMER0_TAILR_R = precarga0;					//Precarga Valor en sec por Frec de Uc	
	TIMER0_CTL_R = TIMER_CTL_TAEN;				//Modulo Timer habilitado.

	return 1;
}// int configurar_Timer(void)
/*************************************************************************************/
