// Configuración uart
#include "varios.h"
#include "Defines.h"
#include "delay.h"

void Init_uart_0(void)
{
   	//Habilitar los perifericos usados en este programa

	SYSCTL_RCGC2_R |=(SYSCTL_RCGC2_GPIOA);
	SYSCTL_RCGC1_R |= (SYSCTL_RCGC1_UART0); //Usar esa palabra equivale a reemplazar poner 1 en el bit 0 para lo de la UART

	//Genero un delay para esperar que se estabilicen los valores de los registros
	delay(2000);

	//Configurar el puerto A
	GPIO_PORTA_DIR_R = 0x02; //Pin 0 como entrada Rx y pin 1 como salida Tx
	GPIO_PORTA_AFSEL_R= 0x03; //Habilitamos la funcion alterna en los dos primeros pines
	GPIO_PORTA_DEN_R |= (0x03); //Habilitar los datos digitales en los pines 0 y 1.

	//Configurar UART0

	UART0_CTL_R = 0; // deshabilitar la UART
	UART0_IBRD_R=162; //Escribimos la parte entera del baudrate 25MHz/(16*9600)
	UART0_FBRD_R=49; //Escribimos la parte flotante del baudrate	integer(0.04166*64 + 0.5)
	UART0_LCRH_R=UART_LCRH_WLEN_8; //Habilitamos para 8 bits(equivalente a escribir 0x60)
	UART0_CTL_R |=(UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE); //Habilitar la UART, equivalente a escribir 0x301
}  //Init_uart

void Desh_uart_0(void)
{
	UART0_CTL_R = 0; // deshabilitar la UART
}
  
void Hab_uart_0(void)
{
	UART0_CTL_R |=(UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE); //Habilitar la UART, equivalente a escribir 0x301
}  //Hab_uart


void Init_uart_1(void)
{
   	//Habilitar los perifericos usados en este programa

	SYSCTL_RCGC2_R |=(SYSCTL_RCGC2_GPIOD);
	SYSCTL_RCGC1_R |= (SYSCTL_RCGC1_UART1); //Usar esa palabra equivale a reemplazar poner 1 en el bit 0 para lo de la UART

	//Genero un delay para esperar que se estabilicen los valores de los registros
	delay(2000);

	//Configurar el puerto D
	GPIO_PORTD_DIR_R |= 0x08; //Pin 2 como entrada Rx y pin 3 como salida Tx
	GPIO_PORTD_AFSEL_R	|= 0x0C; //Habilitamos la funcion alterna en los dos pines de la uart
	GPIO_PORTD_DEN_R |= (0x0C); //Habilitar los datos digitales en los pines.

	//Configurar UART1

	UART1_CTL_R = 0; // deshabilitar la UART
	UART1_IBRD_R=162; //Escribimos la parte entera del baudrate 25MHz/(16*9600)
	UART1_FBRD_R=49; //Escribimos la parte flotante del baudrate	integer(0.04166*64 + 0.5)
	UART1_LCRH_R=UART_LCRH_WLEN_8; //Habilitamos para 8 bits(equivalente a escribir 0x60)
	UART1_CTL_R |=(UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE); //Habilitar la UART, equivalente a escribir 0x301
}  //Init_uart

void Desh_uart_1(void)
{
	UART1_CTL_R = 0; // deshabilitar la UART
}
  
void Hab_uart_1(void)
{
	UART1_CTL_R |=(UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE); //Habilitar la UART, equivalente a escribir 0x301
}  //Hab_uart

