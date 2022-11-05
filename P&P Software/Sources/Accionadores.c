/*Modulo de lectura de los pedales de control del carrusel*/

#include "varios.h"
#include "Defines.h"
#include "Fifo.h"
#include "Accionadores.h"
#include "tiempo.h"
#include "varios.h"
#include "Comunicacion.h"

static t_fifo_handler* cargar;
static Tm_Control* Tm_Accionadores;

char Estado_actual_pedal1=0;
char Estado_actual_pedal2=0;
char Estado_anterior_pedal1=0;
char Estado_anterior_pedal2=0;
char Flanco_Pedal1=0;
char Flanco_Pedal2=0;
char Direccion_carrusel=0;


void Leer_Pedales (void)
{
	if(SWITCH_CARRUSEL)
	{		
		if(Tm_Hubo_periodico(Tm_Accionadores,TP_PEDALES))
		{
				Tm_Baje_periodico(Tm_Accionadores,TP_PEDALES);

				if((PEDAL1) && (PEDAL2))
				{
						Estado_anterior_pedal1=0;
						Estado_anterior_pedal2=0;
				}//PEDALES EN ESPERA
				else if((PEDAL1==0)&&(PEDAL2))
				{
						Estado_actual_pedal1=1;
						Flanco_Pedal1=(Estado_anterior_pedal1 ^ Estado_actual_pedal1) & Estado_actual_pedal1;
						Estado_anterior_pedal1 = Estado_actual_pedal1;
						
						if(Flanco_Pedal1)
						{
							Enviar_Caracter_Uart1('D');
							Agregar_dato_fifo(cargar,'D');	
						}
				}//GIRAR A LA DERECHA
				else if((PEDAL1)&&(PEDAL2==0))
				{
						Estado_actual_pedal2=1;
						Flanco_Pedal2=(Estado_anterior_pedal2 ^ Estado_actual_pedal2) & Estado_actual_pedal2;
						Estado_anterior_pedal2 = Estado_actual_pedal2;
						if(Flanco_Pedal2)
						{
							Enviar_Caracter_Uart1('I');
							Agregar_dato_fifo(cargar,'I');
						}						
				}//GIRAR A LA IZQUIERDA	 
		}
	}
	if(Tm_Hubo_periodico(Tm_Accionadores, 4))
	{
	  Tm_Baje_periodico(Tm_Accionadores, 4);
		Enviar_Uart1();
	}
}
void Servicios_Acc(t_fifo_handler* memo, Tm_Control* tcp)
{
	  cargar = memo;
	  Tm_Accionadores = tcp;
}	
