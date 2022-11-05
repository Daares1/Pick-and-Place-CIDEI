/* Tiempo.h	Definición del módulo de tiempo */
#ifndef TIEMPO_H
#define TIEMPO_H

#define TM_PER_B_ACTIVO			0x01U
#define TM_PER_B_FC				0x02U

#define TM_TOUT_B_ACTIVO		0x01U

typedef unsigned short Tm_Contador;
typedef unsigned char Tm_Num;


typedef struct
	{
	unsigned char banderas;
	Tm_Contador	contador,
				periodo;
	}Tm_Periodico;

typedef struct
	{
	unsigned char estado;
	Tm_Contador	contador;
	}Tm_Timeout;

	
//typedef char Tm_Atender (char atienda);

typedef struct
	{
	Tm_Periodico *pp;
	Tm_Num l_periodo;
	
	Tm_Timeout *tp;
	Tm_Num l_timeout;
	
//	Tm_Atender *atender;
	}Tm_Control;

void Tm_Defina (Tm_Control *tcp,
					 Tm_Periodico *pp,
					 Tm_Num l_periodo,
					 Tm_Timeout *tp,
					 Tm_Num l_timeout);/*,
					 Tm_Atender *atender); */

void Tm_Procese (Tm_Control *tcp);

void Tm_Inicie_periodico (Tm_Control *tcp,
								  Tm_Num num,
								  Tm_Contador periodo);
								  
Tm_Num Tm_Hubo_periodico (const Tm_Control *tcp,
								Tm_Num num);

void Tm_Baje_periodico (Tm_Control *tcp,
				  			   Tm_Num num);

void Tm_Termine_periodico (Tm_Control *tcp,
				  			      Tm_Num num);
								
void Tm_Inicie_timeout (Tm_Control *tcp,
								Tm_Num num,
								Tm_Contador timeout);
								
Tm_Num Tm_Hubo_timeout (const Tm_Control *tcp,
							 Tm_Num num);

void Tm_Termine_timeout (Tm_Control *tcp,
				  			      Tm_Num num);

#endif
