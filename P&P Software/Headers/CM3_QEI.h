#ifndef CM3_QEI_H
#define CM3_QEI_H

#define RESOLUCION_ENCODER 6480

void Init_QEI_0(void);
char Encoder_Direction (void);
int	 Position_Integrator (void);
int  Actual_Count(void);
int  Previous_Count(void);

#endif
