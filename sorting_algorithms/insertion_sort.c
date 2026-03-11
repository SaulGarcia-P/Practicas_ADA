/*
Algoritmo de ordenamiento insertion_sort.
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0 

Este programa implementa el algoritmo de ordenamiento insertion_sort.
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

#define TRUE 1
#define FALSE 0

void Insercion(int *A, int n);

/*
int main(int num_arg, char *argv[])
Recibe: num_arg - Cantidad de argumentos pasados desde la terminal.
        *argv[] - Vector de cadenas que contiene los argumentos (espera el tamaño 'n').
Devuelve: int (0 al finalizar la ejecución).
Función: 
    1. Valida que el usuario proporcione el tamaño del arreglo como parámetro.
    2. Reserva memoria dinámica para un arreglo de enteros de tamaño 'n'.
    3. Lee los elementos de la entrada estándar y los almacena en el arreglo 'A'.
    4. Ejecuta el algoritmo de 'Insercion' (Insertion Sort) cronometrando el proceso 
    con la función 'uswtime'.
    5. Despliega el arreglo resultante y un análisis detallado del rendimiento 
    del sistema (tiempo real, tiempo de CPU y tiempo de entrada/salida).
    6. Libera la memoria dinámica para evitar fugas (memory leaks).
*/

int main(int num_arg, char *argv[]) {

    int i, n;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;

    if (num_arg != 2) {
        printf("\nIndique el tamaño de datos a ordenar\n");
        exit(1);
    }
    n = atoi(argv[1]);

    int *A = malloc(n * sizeof(int));
    if (A == NULL) {
        printf("\nError al intentar reservar memoria para %d elementos\n", n);
        exit(1);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // Inicia medición
    uswtime(&utime0, &stime0, &wtime0);

    Insercion(A, n);

    // Termina medición
    uswtime(&utime1, &stime1, &wtime1);

    for (i = 0; i < n; i++) {
        printf("%d .- %d\n", (i + 1), A[i]);
    }

    // Mostrar resultados
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo E/S)     %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n",
           100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

    free(A);
    return 0;
}

/*
void Insercion(int *A, int n)
Recibe: *A - Puntero al arreglo de enteros que se desea ordenar.
        n  - Número total de elementos presentes en el arreglo.
Devuelve: void
Función: 
    Ordena los elementos del arreglo de forma ascendente mediante el método 
    de inserción directa. El algoritmo divide virtualmente el arreglo en una 
    parte ordenada y otra desordenada; en cada paso, toma un elemento de la 
    parte desordenada y lo "inserta" en la posición correcta dentro de la 
    sección ordenada, desplazando los elementos mayores hacia la derecha.
*/
void Insercion(int *A, int n)
{
	int i, j, temp;

    for(i = 0; i < n-1; i++){
        j = i;
        temp = A[i];
        while(j>0 && temp < A[j-1]){
            A[j] = A[j-1];
            j--;
        } 
        A[j] = temp;
    }
}