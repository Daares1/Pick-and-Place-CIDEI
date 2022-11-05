#include "varios.h"
#include "Defines.h"
#include "CM3_QEI.h"
#include "Delay.h"
#include "varios.h"


void Init_QEI_0(void)
{
	SYSCTL_RCGC1_R  	|=(SYSCTL_RCGC1_QEI0);	// Habilita el reloj del modulo QEI
	SYSCTL_RCGC2_R 		|=(IDX0_PORT); //habilita puerto para entradas Inx0
	SYSCTL_RCGC2_R 		|=(PhA0_PORT); //habilita puerto para entradas PhA
	SYSCTL_RCGC2_R 		|=(PhB0_PORT); //habilita puerto para entradas PhB
		
	delay(2000); // Retardo para estabilizar registros

	
	IDX0_AFSEL_PORT		|=  IDX0_BIT;	//Habilitar función alterna pin IDX0				
	PhA0_AFSEL_PORT		|=	PhA0_BIT;	//Habilitar función alterna pin	PhA0
	PhB0_AFSEL_PORT		|=	PhB0_BIT;	//Habilitar función alterna pin	PhB0

	IDX0_DEN_PORT		|=  IDX0_BIT;	//Habilitar función digital pin IDX0				
	PhA0_DEN_PORT		|=	PhA0_BIT;	//Habilitar función digital pin	PhA0
	PhB0_DEN_PORT		|=	PhB0_BIT;	//Habilitar función digital pin	PhB0

	QEI0_CTL_R |=  (QEI_CTL_VELEN|QEI_CTL_VELDIV_1|QEI_CTL_RESMODE|QEI_CTL_CAPMODE);

	QEI0_MAXPOS_R  	= RESOLUCION_ENCODER-1;					//Configura el valor de los pulsos maximos a ser contados 3239-1=3238
	QEI0_LOAD_R 		= 0x63;					//Configura el numero de ciclos para cada lectura de velocidad
	
	delay(2000); // Retardo para estabilizar registros
	
	QEI0_CTL_R |= QEI_CTL_ENABLE; 	//Habilita el QEI
}

char Encoder_Direction (void)
{
	if(QEI0_STAT_R & QEI_STAT_ERROR)
	 	return 	 ERROR;
	else if (QEI0_STAT_R & QEI_STAT_DIRECTION)
		return	REVERSE_ROTATION;
	else if ((QEI0_STAT_R & QEI_STAT_DIRECTION)==0)
		return	FORWARD_ROTATION;
	else
		return REPOSO;
}

int	 Position_Integrator (void)
{
	return QEI0_POS_R;
}	

int  Actual_Count(void)
{
	return QEI0_COUNT_R;
}
						
int  Previous_Count(void)
{
	 return QEI0_SPEED_R;
}

