#ifndef COMUNICACION_H
#define COMUNICACION_H

void Crear_Buffer(void);
void Enviar_Dato_Uart0(int dato_leido);
void Enviar_Caracter_Uart0(char caracter);
void Enviar_Dato_Uart1(int dato_leido);
void Enviar_Caracter_Uart1(char caracter);
void Nueva_Linea(void);
void Enviar_Uart0(void);
void Enviar_Uart1(void);

#endif
