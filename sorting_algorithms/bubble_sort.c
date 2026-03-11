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

Compilación:
Linux: gcc bubble_sort.c -o Burbuja.exe
Ejecutar como Burbuja.exe _ < numeros10millones.txt > salida.txt

Este programa implementa el algoritmo de ordenamiento Burbuja.
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

void AlgoritmoBurbuja(int *arregloA, int n);

/*
int main(int num_arg, char *argv[])
Recibe: num_arg - Número de argumentos pasados por línea de comandos.
        *argv[] - Arreglo de cadenas de caracteres con los argumentos.
Devuelve: int (0 si la ejecución fue exitosa).
Función: 
    1. Valida que se haya proporcionado el tamaño del arreglo.
    2. Reserva memoria dinámica para 'n' elementos enteros.
    3. Lee los datos de entrada mediante 'scanf'.
    4. Mide el tiempo de ejecución (Real, CPU y E/S) del Algoritmo de Burbuja.
    5. Imprime el arreglo ordenado y las estadísticas de rendimiento.
    6. Libera la memoria utilizada.
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

    AlgoritmoBurbuja(arregloA, n);

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
void AlgoritmoBurbuja(int *arregloA, int n)
Recibe: *arregloA - Puntero al arreglo de enteros que se desea ordenar.
        n         - El tamaño o número de elementos en el arreglo.
Devuelve: void
Función: 
    Ordena los elementos de un arreglo de forma ascendente (de menor a mayor) 
    mediante el método de intercambio directo. Compara pares de elementos 
    adyacentes y los intercambia si están en el orden incorrecto. El proceso 
    se repite hasta que el elemento más grande de cada iteración "flota" hacia 
    la posición correcta al final del arreglo.
*/

void AlgoritmoBurbuja(int *arregloA, int n)
{
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arregloA[j] > arregloA[j + 1]) {
                aux = arregloA[j];
                arregloA[j] = arregloA[j + 1];
                arregloA[j + 1] = aux;
            }
        }
    }
}
