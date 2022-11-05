/* Tiempo.c	Implementación del módulo de tiempo */
#include "varios.h"
#include "Defines.h"
#include "Tiempo.h"
#include "varios.h"

void Tm_Defina (Tm_Control *tcp,
					 Tm_Periodico *pp,
					 Tm_Num l_periodo,
					 Tm_Timeout *tp,
					 Tm_Num l_timeout)/*,
					 Tm_Atender *atender)*/
	{
	Tm_Num n;
	
	tcp->pp = pp;
	tcp->l_periodo = l_periodo;
	for (n = 0; n < l_periodo; ++n, ++pp)
		pp->banderas = 0;
	
	tcp->tp = tp;
	tcp->l_timeout = l_timeout;
	for (n = 0; n < l_timeout; ++n, ++tp)
		tcp->tp[n].contador = 1;
	
//	tcp->atender = atender;
	};

void Tm_Procese (Tm_Control *tcp)
	{
		Tm_Num n;
		Tm_Periodico *pp;
		Tm_Timeout *tp;

		if(TIEMPO_CUMPLIDO_TIMER0)	
		/* Hubo TICK */
		{
			LIMPIAR_TIMER0;
			for (n = 0; n < tcp->l_periodo; ++n, ++pp)
				if (tcp->pp[n].banderas & TM_PER_B_ACTIVO)
					{
					--(tcp->pp[n].contador);
					if ( !(tcp->pp[n].contador))
						{
						tcp->pp[n].contador = tcp->pp[n].periodo;
						tcp->pp[n].banderas |= TM_PER_B_FC;
						};
					};
					
			for (n = 0; n < tcp->l_timeout; ++n, ++tp)
				if (tcp->tp[n].estado & TM_TOUT_B_ACTIVO)
					--(tcp->tp[n].contador);
		}
	};
	
void Tm_Inicie_periodico (Tm_Control *tcp,
								  Tm_Num num,
								  Tm_Contador periodo)
	{
	Tm_Periodico *pp = tcp->pp + num;
	
	if (num >= tcp->l_periodo)
		return;
		
	pp->banderas = TM_PER_B_ACTIVO;
	pp->contador =  periodo;
	pp->periodo = periodo;
	};

Tm_Num Tm_Hubo_periodico (const Tm_Control *tcp,
								Tm_Num num)
	{
		return tcp->pp[num].banderas & TM_PER_B_FC;
	};

void Tm_Baje_periodico (Tm_Control *tcp,
				  			   Tm_Num num)
	{
		tcp->pp[num].banderas &= ~TM_PER_B_FC;
	};
	
void Tm_Termine_periodico (Tm_Control *tcp,
				  			      Tm_Num num)
	{
	tcp->pp[num].banderas = 0;
	};
	
void Tm_Inicie_timeout (Tm_Control *tcp,
								Tm_Num num,
								Tm_Contador timeout)
	{
	if (num >= tcp->l_timeout)
		return;
	
	tcp->tp[num].contador = timeout;
	tcp->tp[num].estado =  TM_TOUT_B_ACTIVO;
	};

Tm_Num Tm_Hubo_timeout (const Tm_Control *tcp,
							 Tm_Num num)
	{
	return !(tcp->tp[num].contador);
	};

void Tm_Termine_timeout (Tm_Control *tcp,
				  			      Tm_Num num)
	{
	tcp->tp[num].estado = 0;
	};
