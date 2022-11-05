#include "varios.h"
#include "Defines.h"
#include "delay.h"
/**************************************************************************************
Funcion: Init_Ports
**************************************************************************************/
char Init_Ports(void)
{
//Habilito los puertos y periféricos respectivos
	SYSCTL_RCGC2_R 		|=(SYSCTL_RCGC2_GPIOF);	
	SYSCTL_RCGC2_R 		|=(SYSCTL_RCGC2_GPIOD);
	SYSCTL_RCGC2_R 		|=(SYSCTL_RCGC2_GPIOH);
	delay(100);	

//Configuro el puerto F COMO SALIDA PARA LOS LEDS
	GPIO_PORTF_AFSEL_R 	&=~(0xF2);					 //deshabilitar funcion alterna
  GPIO_PORTF_ODR_R 	&=~(0xF2);					 //deshabilitar el open drain de los pines
  GPIO_PORTF_DIR_R 	&=~0xF2;					 //CONFIGURACION DEL PUERTO COMO SALIDA DE DATOS PINES:1,4,5,6,7
  GPIO_PORTF_DEN_R 	|=(0xF2);					 //habilitar los datos digitales
	delay(20);

//Configuro el puerto H COMO SALIDAS
	GPIO_PORTH_AFSEL_R 	&=~(0x3);					 //deshabilitar funcion alterna
  GPIO_PORTH_ODR_R 	&=~(0x3);					 //deshabilitar el open drain de los pines
  GPIO_PORTH_DIR_R 	|=(0x3);					 //CONFIGURACION DEL PUERTO COMO SALIDA DE DATOS
  GPIO_PORTH_DEN_R 	|=(0x3);					 //habilitar los datos digitales
	delay(20);

//Configuro el puerto D COMO ENTRADA DE LOS PULSADORES
	GPIO_PORTD_AFSEL_R 	&=~(0x3);					 //deshabilitar funcion alterna
  GPIO_PORTD_ODR_R 	&=~(0x3);					 //habilitar el open drain de los pines
  GPIO_PORTD_DIR_R 	&=~(0x3);					 //CONFIGURACION DEL PUERTO COMO ENTRADA DE DATOS
  GPIO_PORTD_DEN_R 	|=(0x3);					 //hhabilitar los datos digitales en los pines que se van a usar
	delay(20);

	return (1);
}

