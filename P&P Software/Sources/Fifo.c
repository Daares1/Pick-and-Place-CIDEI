#include "fifo.h"


/************************************************************************************/
t_fifo_handler Crear_manejador_fifo(t_datos *arreglo, unsigned int tamano_arreglo){
	t_fifo_handler temp;
	temp.apuntador_arreglo= arreglo;
	temp.indice_lectura=0;
	temp.indice_escritura=0;
	temp.tamano= tamano_arreglo;
	temp.ocupacion=0;
	return temp;
	}

/************************************************************************************/
char Agregar_dato_fifo(t_fifo_handler* manejador_fifo, t_datos dato){
	//Pregunto si hay espacio en la fifo
	if((manejador_fifo->ocupacion)<(manejador_fifo->tamano)){
		manejador_fifo->apuntador_arreglo[manejador_fifo->indice_escritura]=dato;
		(manejador_fifo->ocupacion)++;
		//Si el índice del escritura llego al límite, lo reinicio
		if((manejador_fifo->indice_escritura)>=((manejador_fifo->tamano)-1)){
				manejador_fifo->indice_escritura=0;
			}
			else{
				(manejador_fifo->indice_escritura)++;
			}
		return 1;
	}
	else
	return 0;
}
/************************************************************************************/
t_datos Extraer_dato_fifo(t_fifo_handler* manejador_fifo){
	t_datos valor;
	//Pregunto si hay datos
	if((manejador_fifo->ocupacion)>0)
		{
			//Extraemos dato y decrementamos ocupación de la fifo
			valor=manejador_fifo->apuntador_arreglo[manejador_fifo->indice_lectura];
			(manejador_fifo->ocupacion)--;
			if((manejador_fifo->indice_lectura)>=((manejador_fifo->tamano))-1){
				manejador_fifo->indice_lectura=0;
			}
			else{
				(manejador_fifo->indice_lectura)++;
			}
			return valor;
		
		}
		else
			return 0;
}
/************************************************************************************/

t_datos Husmear_dato_fifo(t_fifo_handler* manejador_fifo){
	if((manejador_fifo->ocupacion)>0)
	{
		return manejador_fifo->apuntador_arreglo[manejador_fifo->indice_lectura];
	}
		else return 0;
}
/************************************************************************************/

unsigned int Numero_datos_fifo(t_fifo_handler* manejador_fifo){
	return manejador_fifo->ocupacion;
}

/************************************************************************************/
unsigned char Porcentaje_ocupacion_fifo(t_fifo_handler* manejador_fifo){
	return (((manejador_fifo->ocupacion)*100)/(manejador_fifo->tamano));
}

/************************************************************************************/

void Borrar_datos_fifo (t_fifo_handler* manejador_fifo)
{
	manejador_fifo->ocupacion=0;
	manejador_fifo->indice_escritura=0;
	manejador_fifo->indice_lectura=0;
}




