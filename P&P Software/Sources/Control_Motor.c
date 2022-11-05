#include "varios.h"
#include "Defines.h"
#include "varios.h"
#include "Control_Motor.h"
#include "Comunicacion.h"
#include "CM3_QEI.h"
#include "CM3_PWM.h"

#define	POSICION_RACK 	RESOLUCION_ENCODER/NUMERO_RACKS

static Tm_Control* Tm_Control_Motor;
static Estructura_Motor_Datos* t_Control_Motor;
static t_fifo_handler* t_Leer_Pedales;

int	  Posicion_carrusel=0;
int		Siguiente_desplazamiento;

int		Direccion_carrusel_puenteH=FORWARD_ROTATION;
int   Integrador_carrusel=0;
int		Set_point_carrusel=180;//Grados
//Variables de control pid
signed int		Accion_proporcional=0;
signed int		Accion_integral=0;
signed int   	Accion_derivativa=0;
double		Accion_PID=0;
int   Error_posicion_carrusel=0;
int   Error_anterior=0;


void Control_Motor(void)
{	
	if(SWITCH_CARRUSEL)
	{
		if(Tm_Hubo_periodico(Tm_Control_Motor, TP_CONTROL_MOTOR))
		{
				Tm_Baje_periodico(Tm_Control_Motor, TP_CONTROL_MOTOR);			
				Accion_PID=0;			
				PWM2_DISABLE_A();	
				PWM2_DISABLE_B();	
				//DETERMINAR POSICIÓN
				
				if(Error_posicion_carrusel < 10)
				{
					Siguiente_desplazamiento=Extraer_dato_fifo(t_Leer_Pedales);
					if(Siguiente_desplazamiento=='D')
					{
						if(Posicion_carrusel<(NUMERO_RACKS-1))
						{
							Posicion_carrusel++;
						}
						else if (Posicion_carrusel>=(NUMERO_RACKS-1))
						{
							Posicion_carrusel=0;
						}	   
					}
					else if(Siguiente_desplazamiento=='I')
					{
						if(Posicion_carrusel>0)
						{
							Posicion_carrusel--;
						}
						else if(Posicion_carrusel<=0)
						{
							Posicion_carrusel=(NUMERO_RACKS-1);
						}
					}		
				}
				Set_point_carrusel=GRADOS_RACK*Posicion_carrusel;
				Integrador_carrusel=RESOLUCION_ENCODER*Set_point_carrusel/360;				
			
				//DETERMINAR ERROR	

				if(Integrador_carrusel==0)
				{
					if((0 < t_Control_Motor->Motor_Integrador_Posicion) && (t_Control_Motor->Motor_Integrador_Posicion < POSICION_RACK*10))
					{
						Error_posicion_carrusel = t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = REVERSE_ROTATION;
					}
					else if(((RESOLUCION_ENCODER - POSICION_RACK*10) < t_Control_Motor->Motor_Integrador_Posicion) && (t_Control_Motor->Motor_Integrador_Posicion < RESOLUCION_ENCODER))
					{
						Error_posicion_carrusel = RESOLUCION_ENCODER - t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion == 0)
					{
						Error_posicion_carrusel = 0;
						Direccion_carrusel_puenteH = STOP_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion == (RESOLUCION_ENCODER - POSICION_RACK))
					{
						Error_posicion_carrusel = RESOLUCION_ENCODER - POSICION_RACK;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;						
					}
					else
					{
						Error_posicion_carrusel = Integrador_carrusel-t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
				}
				else if(Integrador_carrusel == (RESOLUCION_ENCODER - POSICION_RACK))
				{
					if(((RESOLUCION_ENCODER - POSICION_RACK)  < t_Control_Motor->Motor_Integrador_Posicion) && (t_Control_Motor->Motor_Integrador_Posicion < RESOLUCION_ENCODER))
					{
						Error_posicion_carrusel = t_Control_Motor->Motor_Integrador_Posicion - Integrador_carrusel;
						Direccion_carrusel_puenteH = REVERSE_ROTATION;
					}
					else if(((RESOLUCION_ENCODER - (POSICION_RACK*10))  < t_Control_Motor->Motor_Integrador_Posicion) && (t_Control_Motor->Motor_Integrador_Posicion < Integrador_carrusel))
					{
						Error_posicion_carrusel = Integrador_carrusel - t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion == Integrador_carrusel)
					{
						Error_posicion_carrusel=0;
						Direccion_carrusel_puenteH = STOP_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion == 0)
					{
						Error_posicion_carrusel = POSICION_RACK;
						Direccion_carrusel_puenteH = REVERSE_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion < POSICION_RACK*10)
					{
						Error_posicion_carrusel = POSICION_RACK + t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = REVERSE_ROTATION;
					}
					else
					{
						Error_posicion_carrusel = Integrador_carrusel-t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
				}
				else if(Integrador_carrusel == POSICION_RACK)
				{
					if((Integrador_carrusel  < t_Control_Motor->Motor_Integrador_Posicion) && (t_Control_Motor->Motor_Integrador_Posicion < (POSICION_RACK*10)))
					{
						Error_posicion_carrusel = t_Control_Motor->Motor_Integrador_Posicion - Integrador_carrusel;
						Direccion_carrusel_puenteH = REVERSE_ROTATION;
					}
					else if((0  < t_Control_Motor->Motor_Integrador_Posicion) && (t_Control_Motor->Motor_Integrador_Posicion < Integrador_carrusel))
					{
						Error_posicion_carrusel = Integrador_carrusel - t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion == Integrador_carrusel)
					{
						Error_posicion_carrusel=0;
						Direccion_carrusel_puenteH = STOP_ROTATION;
					}
					else if(t_Control_Motor->Motor_Integrador_Posicion == 0)
					{
						Error_posicion_carrusel = POSICION_RACK;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
					else if(((RESOLUCION_ENCODER - POSICION_RACK*10) < t_Control_Motor->Motor_Integrador_Posicion)  && (t_Control_Motor->Motor_Integrador_Posicion < RESOLUCION_ENCODER))
					{
						Error_posicion_carrusel = RESOLUCION_ENCODER - t_Control_Motor->Motor_Integrador_Posicion + POSICION_RACK;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
					else
				  {
						Error_posicion_carrusel = Integrador_carrusel-t_Control_Motor->Motor_Integrador_Posicion;
						Direccion_carrusel_puenteH = FORWARD_ROTATION;
					}
				}
				else if(Integrador_carrusel > t_Control_Motor->Motor_Integrador_Posicion)
				{
					Error_posicion_carrusel=Integrador_carrusel-t_Control_Motor->Motor_Integrador_Posicion;
					Direccion_carrusel_puenteH = FORWARD_ROTATION;
				}
				else if(Integrador_carrusel < t_Control_Motor->Motor_Integrador_Posicion)
				{
					Error_posicion_carrusel = t_Control_Motor->Motor_Integrador_Posicion - Integrador_carrusel;
					Direccion_carrusel_puenteH = REVERSE_ROTATION;
				}
				else if(Integrador_carrusel == t_Control_Motor->Motor_Integrador_Posicion)
				{
					Error_posicion_carrusel = 0;
					Direccion_carrusel_puenteH = STOP_ROTATION;					
				}

				if(Error_posicion_carrusel < 5)
				{
					Direccion_carrusel_puenteH = STOP_ROTATION;			
					Accion_integral = 0;
				}
				//CALCULO PID
				Accion_proporcional =  Error_posicion_carrusel*KP;
				Accion_integral			+= Error_posicion_carrusel*KI;
				Accion_derivativa		=	(Error_posicion_carrusel - Error_anterior)*KD;
				Accion_PID					=	Accion_proporcional +	Accion_integral + Accion_derivativa + 9000;
				Error_anterior = Error_posicion_carrusel;

				
				if(Accion_PID < LIMITE_INF_PWM)
				{
					Accion_PID = 0;
				}
				else if((Accion_PID >= LIMITE_INF_PWM) && (Accion_PID <= LIMITE_SUP_PWM))
				{
					Accion_PID = Accion_PID;
				}
				else if(Accion_PID > LIMITE_SUP_PWM)
				{
					Accion_PID = LIMITE_SUP_PWM;
				}
				Enviar_Caracter_Uart1('S');
				Enviar_Dato_Uart1(Integrador_carrusel);
				Enviar_Caracter_Uart1('P');
				Enviar_Dato_Uart1(t_Control_Motor->Motor_Integrador_Posicion);
				Enviar_Caracter_Uart1('A');	
				Enviar_Dato_Uart1(Accion_PID);				
				Nueva_Linea();	
				
				if(Direccion_carrusel_puenteH == FORWARD_ROTATION)
				{
						PWM2_Duty_A (Accion_PID);
						PWM2_ENABLE_A();
					  PWM2_DISABLE_B();
				}
				else if(Direccion_carrusel_puenteH == REVERSE_ROTATION)
				{
						PWM2_Duty_B (Accion_PID);
						PWM2_ENABLE_B();
					  PWM2_DISABLE_A();
				}
				else if(Direccion_carrusel_puenteH == STOP_ROTATION)
				{
					  PWM2_DISABLE_A();		
						PWM2_DISABLE_B();
				}
			}
	}
	if(Tm_Hubo_periodico(Tm_Control_Motor, 5))
	{
	  Tm_Baje_periodico(Tm_Control_Motor, 5);
		Enviar_Uart1();
	}
}

void Servicios_Motor(t_fifo_handler* memo, Tm_Control* tcp,Estructura_Motor_Datos* t_Motor)
{
	Tm_Control_Motor=tcp;
	t_Leer_Pedales=memo;
	t_Control_Motor=t_Motor;
}
