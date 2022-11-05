#include "varios.h"
#include "Defines.h"
#include "Comunicacion.h"  
#include "varios.h"
#include "Fifo.h"

static t_fifo_handler buffer_comunicacion; 
static char datos_uart[1000];

void Crear_Buffer(void)
{
	buffer_comunicacion=Crear_manejador_fifo(datos_uart, 1000);
}

void Enviar_Dato_Uart0(int dato_leido)
{
	if(Porcentaje_ocupacion_fifo(&buffer_comunicacion)<=95)
	{
//		Agregar_dato_fifo(&buffer_comunicacion,(dato_leido/10000)| 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,((dato_leido%10000)/1000) | 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,(((dato_leido%10000)%1000)/100)| 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,((((dato_leido%10000)%1000)%100)/10)| 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,((((dato_leido%10000)%1000)%100)%10)| 0x30);
	}
}

void Enviar_Caracter_Uart0(char caracter)
{
	Agregar_dato_fifo(&buffer_comunicacion,caracter);
}

void Nueva_Linea(void)
{
	Agregar_dato_fifo(&buffer_comunicacion,ENTER);
	Agregar_dato_fifo(&buffer_comunicacion,CARRIER);
}


void Enviar_Uart0(void)
{

	if(Numero_datos_fifo (&buffer_comunicacion))
	{
   		PUTCHAR_UART0=Extraer_dato_fifo(&buffer_comunicacion);
	}

}

void Enviar_Dato_Uart1(int dato_leido)
{
	if(Porcentaje_ocupacion_fifo(&buffer_comunicacion)<=95)
	{
		Agregar_dato_fifo(&buffer_comunicacion,(dato_leido/10000)| 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,((dato_leido%10000)/1000) | 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,(((dato_leido%10000)%1000)/100)| 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,((((dato_leido%10000)%1000)%100)/10)| 0x30);
		Agregar_dato_fifo(&buffer_comunicacion,((((dato_leido%10000)%1000)%100)%10)| 0x30);
	}
}

void Enviar_Caracter_Uart1(char caracter)
{
	Agregar_dato_fifo(&buffer_comunicacion,caracter);
}

void Enviar_Uart1(void)
{

	if(Numero_datos_fifo (&buffer_comunicacion))
	{
   		PUTCHAR_UART1=Extraer_dato_fifo(&buffer_comunicacion);
	}

}
