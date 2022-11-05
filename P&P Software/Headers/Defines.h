/**************************************************************************************
 				DEFINES
**************************************************************************************/	
#ifdef DEFINES_LM3S1512
#include "lm3s1512.h"
#define SW1				(GPIO_PORTD_DATA_R & (0x01))		//Pin correspondiente a la entrada del pulsador SW1(S2)
#define SW2				(GPIO_PORTD_DATA_R & (0x02))		//Pin correspondiente a la entrada del pulsador SW2(S3)
#define SW3				(GPIO_PORTE_DATA_R & (0x10))		//Pin correspondiente a la entrada del pulsador SW3(S4)
#define SW4				(GPIO_PORTE_DATA_R & (0x20))		//Pin correspondiente a la entrada del pulsador SW4(S5)
#define SW5				(GPIO_PORTD_DATA_R & (0x10))		//Pin correspondiente a la entrada del pulsador SW5(S6)
#define SW6				(GPIO_PORTD_DATA_R & (0x20))		//Pin correspondiente a la entrada del pulsador SW6(S7)
#define SW7				(GPIO_PORTD_DATA_R & (0x40))		//Pin correspondiente a la entrada del pulsador SW7(S8)
#define SW8				(GPIO_PORTD_DATA_R & (0x80))		//Pin correspondiente a la entrada del pulsador SW8(S9)

#define LED1 0x01
#define LED2 0x02
#define LED3 0x04
#define LED4 0x08
#define LED5 0x10
#define LED6 0x20
#define LED7 0x40
#define LED8 0x80

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define LEDS			GPIO_PORTF_DATA_R		
#define LED1_ON			GPIO_PORTF_DATA_R |= (LED1)		//Pin correspondiente al led 1 de la tarjeta D3
#define LED2_ON			GPIO_PORTF_DATA_R |= (LED2)		//Pin correspondiente al led 2 de la tarjeta D4
#define LED3_ON			GPIO_PORTF_DATA_R |= (LED3)		//Pin correspondiente al led 3 de la tarjeta D5
#define LED4_ON			GPIO_PORTF_DATA_R |= (LED4)		//Pin correspondiente al led 4 de la tarjeta D6
#define LED5_ON			GPIO_PORTF_DATA_R |= (LED5)		//Pin correspondiente al led 5 de la tarjeta D7
#define LED6_ON			GPIO_PORTF_DATA_R |= (LED6)		//Pin correspondiente al led 6 de la tarjeta D8
#define LED7_ON			GPIO_PORTF_DATA_R |= (LED7)		//Pin correspondiente al led 7 de la tarjeta D9
#define LED8_ON			GPIO_PORTF_DATA_R |= (LED8)		//Pin correspondiente al led 8 de la tarjeta D10

#define DISPLAY 		GPIO_PORTG_DATA_R  				//Pines de los Displays 7 Segmentos
#define DISPLAY_1 		GPIO_PORTH_DATA_R |=	(0x08)		//Pin correspondiente al Display 1
#define DISPLAY_2 		GPIO_PORTH_DATA_R |=	(0x04)		//Pin correspondiente al Display 2
#define DISPLAY_3 		GPIO_PORTH_DATA_R |=	(0x02)		//Pin correspondiente al Display 3
#define DISPLAY_4 		GPIO_PORTH_DATA_R |=	(0x01)		//Pin correspondiente al Display 4
#define DISPLAYS		GPIO_PORTH_DATA_R = (0x0F)


//UART 0
#define HAY_DATO_UART0          ((UART0_RIS_R & UART_RIS_RXRIS) == (UART_RIS_RXRIS))
#define NO_HAY_DATO_UART0       ((UART0_RIS_R & UART_RIS_RXRIS) != (UART_RIS_RXRIS))
#define LIMPIAR_UART0           UART0_ICR_R |= UART_ICR_RXIC
#define GETCHAR_UART0           UART0_DR_R
#define PUTCHAR_UART0		        UART0_DR_R

//UART 1
#define HAY_DATO_UART1       	  ((UART1_RIS_R & UART_RIS_RXRIS) == (UART_RIS_RXRIS))
#define NO_HAY_DATO_UART1       ((UART1_RIS_R & UART_RIS_RXRIS) != (UART_RIS_RXRIS))
#define LIMPIAR_UART1			      UART1_ICR_R |= UART_ICR_RXIC
#define GETCHAR_UART1           UART1_DR_R
#define PUTCHAR_UART1		        UART1_DR_R

//TIMER 0
#define TIEMPO_CUMPLIDO_TIMER0	TIMER0_RIS_R & TIMER_RIS_TATORIS  //Pregunta por la bandera del timer0
#define LIMPIAR_TIMER0			TIMER0_ICR_R = TIMER_ICR_TATOCINT //Limpia la bandera del timer0

//ASCII ESPECIAL
#define  SOH  0x01	
#define  EOT  0x04
#define  ACK  0x06
#define  XON  0x11
#define  XOFF 0x13
#define  NAK  0x15
#define  CAN 0x18

//CONTROL DE ERRORES EN COMUNICACIÓN
#define  LIMITE_NAK 10

//DEFINE PARA EL BUZZER
#define BUZZER_ON 	LED3_ON
#define BUZZER_OFF	LEDS &= ~LED3

//DEFINES PARA LA P&P
#define SWITCH_PICK_PLACE			SW1
#define SENSOR_FINAL_CARRERA_NC	 	SW8
#define SENSOR_FINAL_CARRERA_NA	 	SW7		
#define ELECTROVALVULA_ON 			LED2_ON
#define ELECTROVALVULA_OFF 			LEDS &= ~LED2

//DEFINES PARA EL CARRUSEL
#define SWITCH_CARRUSEL				SW2
#define PEDAL1					 	SW6
#define PEDAL2					 	SW5	



//DEFINES PARA EL ENCODER
#define IDX0_PORT					SYSCTL_RCGC2_GPIOD
#define PhA0_PORT					SYSCTL_RCGC2_GPIOD
#define	PhB0_PORT					SYSCTL_RCGC2_GPIOF
#define IDX0_AFSEL_PORT				GPIO_PORTD_AFSEL_R	
#define PhA0_AFSEL_PORT				GPIO_PORTD_AFSEL_R
#define PhB0_AFSEL_PORT				GPIO_PORTF_AFSEL_R
#define IDX0_DEN_PORT				GPIO_PORTD_DEN_R	
#define PhA0_DEN_PORT				GPIO_PORTD_DEN_R
#define PhB0_DEN_PORT				GPIO_PORTF_DEN_R
#define IDX0_BIT					BIT0
#define PhA0_BIT					BIT1
#define PhB0_BIT					BIT0
					

#endif
/*************************************************************************************/
#ifdef DEFINES_LM3S1968
#include "lm3s1968.h"

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

//DEFINES PARA EL BUZZER
#define BUZZER_GPIO_H1_O  GPIO_PORTH_DATA_R
#define BUZZER_ON 	BUZZER_GPIO_H1_O |=	BIT1
#define BUZZER_OFF	BUZZER_GPIO_H1_O &= ~BIT1

//DEFINES PARA EL TIMER
//TIMER 0
#define TIEMPO_CUMPLIDO_TIMER0	TIMER0_RIS_R & TIMER_RIS_TATORIS  //Pregunta por la bandera del timer0
#define LIMPIAR_TIMER0			TIMER0_ICR_R = TIMER_ICR_TATOCINT //Limpia la bandera del timer0

//DEFINES PARA P&P
#define ONOFF_PP_GPIO_F1_I  			(GPIO_PORTF_DATA_R & (BIT1))
#define NC_GPIO_F5_I					(GPIO_PORTF_DATA_R & (BIT5))
#define NA_GPIO_F4_I					(GPIO_PORTF_DATA_R & (BIT4))
#define SWITCH_PICK_PLACE 				ONOFF_PP_GPIO_F1_I
#define SENSOR_FINAL_CARRERA_NC			NC_GPIO_F5_I
#define SENSOR_FINAL_CARRERA_NA			NA_GPIO_F4_I
#define CONTROL_VAL_GPIO_H0_O				GPIO_PORTH_DATA_R
#define ELECTROVALVULA_OFF				CONTROL_VAL_GPIO_H0_O |= BIT0
#define ELECTROVALVULA_ON				CONTROL_VAL_GPIO_H0_O &=~BIT0

//DEFINES PARA EL CARRUSEL
#define ONOFF_MOTOR_GPIO_D1_I			(GPIO_PORTD_DATA_R & (BIT1))
#define PEDAL1_GPIO_F6_I				(GPIO_PORTF_DATA_R & (BIT6))
#define PEDAL2_GPIO_F7_I				(GPIO_PORTF_DATA_R & (BIT7))
#define SWITCH_CARRUSEL					ONOFF_MOTOR_GPIO_D1_I
#define PEDAL1					 		PEDAL1_GPIO_F6_I
#define PEDAL2					 		PEDAL2_GPIO_F7_I

//DEFINES PARA EL ENCODER
#define IDX0_PORT					SYSCTL_RCGC2_GPIOD
#define PhA0_PORT					SYSCTL_RCGC2_GPIOC
#define	PhB0_PORT					SYSCTL_RCGC2_GPIOF
#define IDX0_AFSEL_PORT				GPIO_PORTD_AFSEL_R	
#define PhA0_AFSEL_PORT				GPIO_PORTC_AFSEL_R
#define PhB0_AFSEL_PORT				GPIO_PORTF_AFSEL_R
#define IDX0_DEN_PORT				GPIO_PORTD_DEN_R	
#define PhA0_DEN_PORT				GPIO_PORTC_DEN_R
#define PhB0_DEN_PORT				GPIO_PORTF_DEN_R
#define IDX0_BIT					BIT0
#define PhA0_BIT					BIT4
#define PhB0_BIT					BIT0

#define GETCHAR_UART0           UART0_DR_R
#define PUTCHAR_UART0		        UART0_DR_R
#define PUTCHAR_UART1						UART1_DR_R

#endif
/*************************************************************************************/
