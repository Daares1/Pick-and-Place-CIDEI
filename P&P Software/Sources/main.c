/*MDNP MAQUINA P&P SE*/
//Includes de servicios

#include "Fifo.h"
#include "tiempo.h"
#include "varios.h"
#include "Defines.h"
#include "Comunicacion.h"

//Includes de configuración
#include "CM3_MCU.h"
#include "CM3_PORTS.h"
#include "CM3_UART.h"
#include "CM3_TIMER.h"
#include "CM3_QEI.h"
#include "CM3_PWM.h"

//Includes de programa
#include "Accionadores.h"
#include "Control_valvula.h"
#include "Encoder.h"
#include "Control_Motor.h"

static Tm_Periodico t_periodicos[TM_NUM_PERIODICOS];
static Tm_Timeout t_timeouts[TM_NUM_TIMEOUTS];

static Tm_Control c_tiempo;
static Estructura_Motor_Datos c_motor;
static t_fifo_handler myfifo; 
static char datos[BUFFER_SIZE];



int main(void)
{	

 	Init_MCU();
	Init_Ports();
	Init_uart_1();
	Init_QEI_0();
	PWM2_Init(FRECUENCIA_PWM,0, 0);//Frecuencia 1KHz, Ciclo Util A, Ciclo Util B
	Config_Timer_0(TM_BASE);

	myfifo=Crear_manejador_fifo(datos, BUFFER_SIZE);
	Crear_Buffer();

	Tm_Defina(&c_tiempo, t_periodicos, TM_NUM_PERIODICOS,t_timeouts, TM_NUM_TIMEOUTS);

	Tm_Inicie_timeout(&c_tiempo,TOUT_BUZZER,TM_TOUT_BUZZER);
	Tm_Inicie_periodico (&c_tiempo,TP_FINAL_CARRERA,TM_TP_FINAL_CERRERA);
	Tm_Inicie_periodico (&c_tiempo,TP_PEDALES,TM_TP_PEDALES);
	Tm_Inicie_periodico (&c_tiempo,TP_ENCODER,TM_TP_ENCODER);
	Tm_Inicie_periodico (&c_tiempo,TP_CONTROL_MOTOR,TM_TP_CONTROL_MOTOR);
	Tm_Inicie_periodico (&c_tiempo,4,10);
	Tm_Inicie_periodico (&c_tiempo,5,10);

	Servicios_Acc(&myfifo,&c_tiempo);
	Servicios_Final_Carrera(&c_tiempo);
	Servicios_Encoder(&c_tiempo,&c_motor);
	Servicios_Motor(&myfifo,&c_tiempo,&c_motor);
	
	PWM2_Duty_A (25000);
	PWM2_ENABLE_A();
	
	ELECTROVALVULA_OFF;

	BUZZER_ON;
	while(!Tm_Hubo_timeout(&c_tiempo, TOUT_BUZZER))
	{
		Tm_Procese(&c_tiempo);
	}
	BUZZER_OFF;

	while(Position_Integrator()!=0)
	{
		PWM2_Duty_A (15000);
		PWM2_ENABLE_A();		
	}
	
	PWM2_DISABLE_A();
	
	while(1)
	{	
		Tm_Procese(&c_tiempo); 			
		Leer_Pedales();	
		Leer_Final_Carrera(); 
		Lectura_Encoder();
		Control_Motor();
	}
}
