//Modulo para la lectura del encoder de la P&P

#include "varios.h"
#include "Defines.h"
#include "Encoder.h"
#include "varios.h"
#include "CM3_QEI.h"



static Tm_Control* Tm_Encoder;
static Estructura_Motor_Datos* Motor;
int 	Delta_posicion=0;
int 	Velocidad=0;
int 	Integrador_posicion_anterior=0;	  	
int 	Integrador_posicion=0;
char	Direccion=0;
int 	Angulo=0;


void Lectura_Encoder(void)
{
	if(Tm_Hubo_periodico(Tm_Encoder, TP_ENCODER))
	{
		Tm_Baje_periodico(Tm_Encoder, TP_ENCODER);
		Direccion=Encoder_Direction();
		Integrador_posicion= Position_Integrator();
		if(Direccion==FORWARD_ROTATION)
		{
			if((Integrador_posicion-Integrador_posicion_anterior)<0)
			{
				Delta_posicion=(RESOLUCION_ENCODER-Integrador_posicion_anterior)+Integrador_posicion;
			}
			else
			{
				Delta_posicion=Integrador_posicion-Integrador_posicion_anterior;
			}

		}
		else if(Direccion==REVERSE_ROTATION)
		{
			if(Integrador_posicion_anterior>=Integrador_posicion)
			{
				Delta_posicion=Integrador_posicion_anterior-Integrador_posicion;
			}
			else
			{
				Delta_posicion=(RESOLUCION_ENCODER-Integrador_posicion)+Integrador_posicion_anterior;
			}
		}
		else if(Direccion==ERROR)
		{
			BUZZER_ON;
		}
		Velocidad = (Delta_posicion*60*PERIODO_ENCODER)/RESOLUCION_ENCODER;
		Integrador_posicion_anterior=Integrador_posicion;
		Angulo=(360*Integrador_posicion)/RESOLUCION_ENCODER;
	}

	Motor->Motor_Velocidad=Velocidad;
	Motor->Motor_Angulo=Angulo;
	Motor->Motor_Direccion=Direccion;
	Motor->Motor_Integrador_Posicion=Integrador_posicion;
}

void Servicios_Encoder(Tm_Control* tcp,Estructura_Motor_Datos* t_Motor)
{
	 Tm_Encoder = tcp;
	 Motor=t_Motor;
}


