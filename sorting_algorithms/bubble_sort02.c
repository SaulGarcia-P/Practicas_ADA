/*
Algoritmo de ordenamiento. Burbuja.
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

Este programa implementa el algoritmo de ordenamiento Burbuja optimizado.
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

#define TRUE 1
#define FALSE 0

void AlgoritmoBurbujaOpt2(int *arregloA, int n);

/*
int main(int num_arg, char *argv[])
Recibe: num_arg - Número de argumentos recibidos por la línea de comandos.
        *argv[] - Arreglo de cadenas con los parámetros (espera el tamaño 'n').
Devuelve: int (0 si la ejecución finaliza correctamente).
Función: 
    1. Valida la recepción del tamaño del arreglo como argumento de entrada.
    2. Reserva dinámicamente el bloque de memoria necesario para 'n' enteros.
    3. Pobla el arreglo mediante la lectura de datos (redirigidos o manuales).
    4. Ejecuta el 'AlgoritmoBurbujaOpt2' bajo un marco de medición temporal.
    5. Utiliza 'uswtime' para obtener métricas de tiempo real, sistema y usuario.
    6. Presenta los resultados del ordenamiento y el análisis de rendimiento de la CPU.
    7. Garantiza la liberación de memoria (free) antes del cierre del proceso.
*/

int main(int num_arg, char *argv[]) {

    int i, n;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;

    if (num_arg != 2) {
        printf("\nIndique el tamaño de datos a ordenar\n");
        exit(1);
    }
    n = atoi(argv[1]);

    int *arregloA = malloc(n * sizeof(int));
    if (arregloA == NULL) {
        printf("\nError al intentar reservar memoria para %d elementos\n", n);
        exit(1);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &arregloA[i]);
    }

    // Inicia medición
    uswtime(&utime0, &stime0, &wtime0);

    AlgoritmoBurbujaOpt2(arregloA, n);

    // Termina medición
    uswtime(&utime1, &stime1, &wtime1);

    for (i = 0; i < n; i++) {
        printf("%d .- %d\n", (i + 1), arregloA[i]);
    }

    // Mostrar resultados
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo E/S)     %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n",
           100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

    free(arregloA);
    return 0;
}

/*
void AlgoritmoBurbujaOpt2(int *arregloA, int n)
Recibe: *arregloA - Puntero al arreglo de enteros.
        n         - Tamaño del arreglo.
Devuelve: void
Función: 
    Ordena el arreglo mediante el método de burbuja optimizado con una bandera 
    de control ('cambios'). Esta variante reduce significativamente el tiempo 
    de ejecución en arreglos que ya están parcial o totalmente ordenados, 
    deteniendo el proceso si en una pasada completa no se realizó ningún intercambio.
*/
void AlgoritmoBurbujaOpt2(int *arregloA, int n){

	int i = 0;
    int j, aux;
    int cambios = TRUE;
	
	while(i<= n-2 && cambios != FALSE){
        cambios = FALSE;

        for(j = 0; j < (n-2)-i; j++){
            if(arregloA[j] < arregloA[j+1]){
                aux = arregloA[j];
                arregloA[j] = arregloA[j+1];
                arregloA[j+1] = aux;
                cambios = TRUE;
            }
        }
        i = i+1;
    }
}