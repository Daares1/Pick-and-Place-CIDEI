#ifndef CONTROL_MOTOR_H
#define CONTROL_MOTOR_H
#include "Tiempo.h"
#include "Fifo.h"
#include "Encoder.h"

void Control_Motor(void);
void Servicios_Motor(t_fifo_handler* memo, Tm_Control* tcp, Estructura_Motor_Datos* t_Motor);

#endif
