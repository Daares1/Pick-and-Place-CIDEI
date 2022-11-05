/*Modulo de lectura del sensor final de carrera */

#include "varios.h"
#include "Defines.h"
#include "Fifo.h"
#include "Control_valvula.h"
#include "tiempo.h"
#include "varios.h"

static Tm_Control* Tm_Valvula;
char Estado_actual_sensor=0;
char Estado_anterior_sensor=0;
char Estado_valvula='A';
char Estado_nuevo_valvula='A';
char valvula=0;
char Flanco=0;

void Leer_Final_Carrera(void)
{	 		  
  if(Tm_Hubo_periodico(Tm_Valvula,TP_FINAL_CARRERA))
	{
		Tm_Baje_periodico(Tm_Valvula,TP_FINAL_CARRERA);
		if(SWITCH_PICK_PLACE)
		{	
			BUZZER_OFF;			
		 	if((SENSOR_FINAL_CARRERA_NC!=0)&&(SENSOR_FINAL_CARRERA_NA==0))
			{
				Estado_actual_sensor=1;
				Flanco=(Estado_anterior_sensor ^ Estado_actual_sensor) & Estado_actual_sensor;
				Estado_anterior_sensor = Estado_actual_sensor;
				if(Flanco)
				{
					valvula ^=0x01;
					if(valvula)
					{
						Estado_nuevo_valvula='A';
					}
					else
					{
						Estado_nuevo_valvula='P';
					}
				}
			}//CONMUTAR VÁLVULA
			else if(((SENSOR_FINAL_CARRERA_NC!=0)&&(SENSOR_FINAL_CARRERA_NA!=0)) || ((SENSOR_FINAL_CARRERA_NC==0)&&(SENSOR_FINAL_CARRERA_NA==0)))
			{
//				BUZZER_ON;
			}//ERROR SENSOR FINAL DE CARRERA
			else
			{
				Estado_anterior_sensor=0;
			}//SENSOR FINAL CARRERA EN ESTADO DE ESPERA
		}//P&P ON/OFF
		Estado_valvula = Estado_nuevo_valvula;
	 	if(Estado_valvula == 'P')
		{
			 ELECTROVALVULA_OFF;
		}
		else if(Estado_valvula =='A')
		{
			 ELECTROVALVULA_ON;
		} 
	}

}

void Servicios_Final_Carrera(Tm_Control* tcp)
{
	 Tm_Valvula = tcp;
}

