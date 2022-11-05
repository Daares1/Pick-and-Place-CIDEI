/* Definiciones generales */


#ifndef VARIOS_H
#define VARIOS_H

#define DEFINES_LM3S1968
#define SI	1
#define NO	0

#define ENTER 	'\n'
#define	CARRIER	'\r'

/*BUFFER*/
#define BUFFER_SIZE		10

/*Número de periodos y timeouts máx*/
#define TM_NUM_PERIODICOS		8
#define TM_NUM_TIMEOUTS			6

/*Tiempos*/
#define TM_BASE	 		0.001
#define TIC_BASE 		1/TM_BASE
#define TICS1MSEG		0.001*TIC_BASE
#define TICS100MSEG 	0.1*TIC_BASE 
#define TICS1SEG 		1*TIC_BASE


/*--------Timeouts--------*/
#define TOUT_BUZZER	0
#define TM_TOUT_BUZZER TICS100MSEG*5
/*------------------------*/

/*Periodos*/
#define TP_FINAL_CARRERA 		0
#define TP_PEDALES 				1
#define TP_ENCODER				2
#define TP_CONTROL_MOTOR		3
#define TM_TP_FINAL_CERRERA 	TICS100MSEG/2
#define TM_TP_PEDALES 			TICS100MSEG/2
#define TM_TP_ENCODER			TICS100MSEG
#define TM_TP_CONTROL_MOTOR		TICS100MSEG
#define PERIODO_ENCODER			10
/**/

//ENCODER
#define REPOSO				3
#define ERROR 				2
#define STOP_ROTATION 		2
#define REVERSE_ROTATION	1
#define	FORWARD_ROTATION	0

//CONTROL MOTOR
#define NUMERO_RACKS	30
#define GRADOS_RACK		360/NUMERO_RACKS
#define	KP						1
#define KI						2
#define KD						0.8

//PWM
#define FRECUENCIA_PWM 		25000   //FRECUENCIA=(25MHz/RECUENCIA_PWM)->1000Hz
#define	LIMITE_INF_PWM		9500		
#define LIMITE_SUP_PWM		11500	

#endif
