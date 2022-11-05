#ifndef ENCODER_H
#define ENCODER_H
#include "Tiempo.h"


typedef struct 
	{
		int	Motor_Velocidad;
		int			Motor_Angulo;
		char			Motor_Direccion;
		int	Motor_Integrador_Posicion;
	} Estructura_Motor_Datos;

void Lectura_Encoder(void);
void Servicios_Encoder(Tm_Control* tcp,Estructura_Motor_Datos* t_Motor);

#endif
