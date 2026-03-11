/*
Implementacion código de ordenamiento con Arbol Binario de Búsqueda y recorrido InOrden
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

DESCRIPCIÓN: Implementación de un algoritmo de ordenamiento utilizando un Árbol Binario de Búsqueda (ABB)
y un recorrido InOrden. El algoritmo inserta cada elemento del arreglo en el ABB y luego realiza un
recorrido InOrden para obtener los elementos en orden ascendente.

OBSERVACIONES: El usuario debe proporcionar un arreglo de números enteros y su tamaño.

COMPILACIÓN: gcc OrdenamientoConABB-c -o OrdenamientoConABB

EJECUCIÓN:	./OrdenamientoConABB {elementos a ordenar}  < lista_caracteres.txt
			./OrdenamientoConABB {elementos a ordenar}  < lista_caracteres.txt > salida.txt
*/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include "TADArbol_bin.h"	
#include <string.h>
#include "tiempo.h"

// PROTOTIPO DE FUNCIONES
void AlgoritmoOrdenamientoConABB(int *A, int n);
void InsertABB(arbol_binario *a, elemento e);
void GuardarInOrden(arbol_binario *a, elemento *arregloOrdenado, int *indice);

/*
int main(int num_args, char *cadena_args[])
Recibe: num_args     - Número de argumentos proporcionados en la terminal.
        *cadena_args - Vector de strings con los argumentos (cadena_args[1] es 'n').
Devuelve: int (0 si el programa finaliza exitosamente).
Función: 
    1. Valida la entrada del parámetro 'n' (cantidad de elementos).
    2. Reserva memoria dinámica para el arreglo de datos 'A'.
    3. Captura el tiempo inicial mediante 'uswtime'.
    4. Ejecuta 'AlgoritmoOrdenamientoConABB', el cual inserta los elementos en 
    un árbol binario y realiza un recorrido in-order para ordenarlos.
    5. Mide los tiempos finales y calcula el desempeño de la CPU y el sistema.
    6. Presenta los resultados en formatos decimal y exponencial para un análisis 
    exhaustivo de la complejidad logarítmica.
    7. Finaliza el proceso liberando los recursos.
*/

int main(int num_args, char *cadena_args[])
{
	// Variables para medición de tiempos
	double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

	// Variables para el algoritmo
	int i, n, *A;

	// Recibir por argumento el tamaño de n
	if (num_args != 2)
	{
		printf("\nIndique el tamanio de n - Ejemplo: %s 100\n", cadena_args[0]);
		exit(1);
	}
	// Tomar el argumento del main
	n = atoi(cadena_args[1]); // n

	// Apartar memoria para n números enteros
	A = malloc(n * sizeof(long));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}

	// Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	uswtime(&utime0, &stime0, &wtime0);

	AlgoritmoOrdenamientoConABB(A, n);

	// Evaluar los tiempos de ejecución
	uswtime(&utime1, &stime1, &wtime1);

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
	free(A);

	return 0;
}

// DECLARACIÓN DE FUNCIONES


/*
void AlgoritmoOrdenamientoConABB(int *A, int n);
Descripción: Implementa el algoritmo de ordenamiento utilizando un Árbol Binario de Búsqueda (ABB)
y un recorrido InOrden.
Recibe: int *A y int n (Arreglo de números enteros y su tamaño)
Devuelve:
Observaciones: El usuario debe proporcionar un arreglo de números enteros y su tamaño.
*/
void AlgoritmoOrdenamientoConABB(int *A, int n)
{
	//Declaración de variables
	arbol_binario a;
	elemento e, *arregloOrdenado;
	int i;

	// Apartar memoria para n elementos ordenados
	arregloOrdenado = malloc(n * sizeof(elemento));
	if (arregloOrdenado == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}

	Initialize(&a);
	//Insertar cada elemento del arreglo en el ABB
	for (i = 0; i < n; i++)
	{
		e.num = A[i];
		InsertABB(&a, e);
	}
	//Ordenar los elementos mediante un recorrido InOrden y guardarlos en el arreglo
	i = 0;
	GuardarInOrden(&a, arregloOrdenado, &i);

	// Liberar memoria del árbol y del arreglo ordenado
	free(arregloOrdenado);
	Destroy(&a);
}

/*
void InsertABB(arbol_binario *a, elemento e);
Descripción: Recibe un árbol binario a y un elemento e, inserta el elemento e en el árbol binario de búsqueda a.
Recibe: arbol_binario *a y un elemento e (Referencia al árbol "a" a operar y elemento a insertar en el árbol)
Devuelve:
Observaciones: El usuario ha creado un árbol binario y a tiene la referencia a él.
*/
void InsertABB(arbol_binario *a, elemento e)
{
	// Caso 1: El árbol está vacío, se crea la raíz
	if (Empty(a))
	{
		// Se puede usar NewLeftSon o NewRightSon, ya que no hay padre
		NewLeftSon(a, NULL, e);
	}
	else
	{
		// Caso 2: El árbol ya tiene nodos, se busca la posición adecuada

		posicion actual = *a; // Comenzamos desde la raíz

		// Bucle para recorrer el árbol hasta encontrar dónde insertar
		while (1)
		{

			// Si el nuevo valor es menor que el valor actual
			if (e.num < actual->e.num)
			{

				// Si no hay hijo izquierdo, se inserta ahí
				if (actual->izq == NULL)
				{
					NewLeftSon(a, actual, e);

					break; // Inserción realizada, salimos del bucle
				}
				else
				{

					// Si hay hijo izquierdo, seguimos recorriendo
					actual = actual->izq;
				}
			}
			// Si el nuevo valor es mayor que el valor actual
			else if (e.num > actual->e.num)
			{

				// Si no hay hijo derecho, se inserta ahí
				if (actual->der == NULL)
				{
					NewRightSon(a, actual, e);

					break; // Inserción realizada, salimos del bucle
				}
				else
				{

					// Si hay hijo derecho, seguimos recorriendo
					actual = actual->der;
				}
			}
			// Si el valor ya existe en el árbol, no se inserta duplicado

			else
			{
				break; // No se hace nada, salimos del bucle
			}
		}
	}
}

/*
void GuardarInOrden(arbol_binario *a, elemento arregloOrdenado[], int *indice);
Descripción: Recorre el árbol en orden y guarda los valores en un arreglo
Recibe: arbol_binario *a, elemento arregloOrdenado[] y int *indice (Referencia al árbol "a", arreglo donde se guardarán los elementos y puntero al índice actual del arreglo)
Devuelve:
Observaciones: El usuario ha creado un árbol binario y a tiene la referencia a él,
*/

void GuardarInOrden(arbol_binario *a, elemento arregloOrdenado[], int *indice)
{
	// Verifica si el árbol no está vacío
	if (!Empty(a))
	{
		// Paso 1: Recorrer el subárbol izquierdo
		GuardarInOrden(&((*a)->izq), arregloOrdenado, indice);

		// Paso 2: Guardar el valor del nodo actual en el arreglo
		arregloOrdenado[*indice] = (*a)->e;
		(*indice)++; // Avanza al siguiente espacio del arreglo

		// Paso 3: Recorrer el subárbol derecho
		GuardarInOrden(&((*a)->der), arregloOrdenado, indice);
	}
}