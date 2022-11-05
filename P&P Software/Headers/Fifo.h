#ifndef FIFO_H
#define FIFO_H

#define t_datos	char

typedef struct 
	{
		t_datos *apuntador_arreglo;
		unsigned int indice_lectura;
		unsigned int indice_escritura;
		unsigned int tamano;
		unsigned int ocupacion;
	} t_fifo_handler;

/*Prototipos de funciones*/

t_fifo_handler Crear_manejador_fifo(t_datos *arreglo, unsigned int tamano_arreglo);

char Agregar_dato_fifo(t_fifo_handler* manejador_fifo, t_datos dato);

t_datos Extraer_dato_fifo(t_fifo_handler* manejador_fifo);

t_datos Husmear_dato_fifo(t_fifo_handler* manejador_fifo);

unsigned int Numero_datos_fifo(t_fifo_handler* manejador_fifo);

unsigned char Porcentaje_ocupacion_fifo(t_fifo_handler* manejador_fifo);

void Borrar_datos_fifo (t_fifo_handler* manejador_fifo);


#endif        //  #ifndef FIFO_H

