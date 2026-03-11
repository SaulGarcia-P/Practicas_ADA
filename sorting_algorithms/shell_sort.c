/*
IMPLEMENTACION DEL ALGORITMO DE SHELL PARA ORDENAR UN CONJUNTO DE ELEMENTOS
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

DESCRIPCION: Este código ordena un arreglo de n elementos de menor a mayor utilizando el algoritmo Shell,
el cual mejora el rendimiento del método de inserción directa. El algoritmo compara y ordena elementos
que se encuentran a cierta distancia entre sí (definida por un intervalo o “gap”), reduciendo progresivamente
este intervalo hasta llegar a 1. De esta forma, los elementos se van acercando a su posición final, logrando
una lista completamente ordenada con menos comparaciones y movimientos que el método de inserción tradicional.

OBSERVACIONES: El tamanio del arreglo debe ser un numero entero positivo.

COMPILACION PARA GENERAR EL CODIGO:

Windows: gcc shell.c tiempo.c -o shell -lm
Linux: gcc shell.c tiempo.c -o shell -lm

EJECUCION:
    shell.exe tamanio_arreglo < numeros10millones.txt > salida_shell.txt

*/

// LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tiempo.h"

void algoritmo_shell(int n, int *A);

/*
int main(int argc, char *argv[])
Recibe: argc   - El número de argumentos pasados por la línea de comandos.
        *argv[] - El vector de argumentos (donde argv[1] es el tamaño 'n').
Devuelve: int (0 si el programa finaliza correctamente).
Función: 
    1. Valida que se haya ingresado el número de elementos como argumento.
    2. Reserva memoria dinámica para un arreglo 'A' de tamaño 'n'.
    3. Carga los datos enteros desde la entrada estándar (stdin).
    4. Ejecuta el 'algoritmo_shell', midiendo el tiempo de ejecución mediante 'uswtime'.
    5. Reporta el rendimiento en tiempo Real, de Usuario (CPU) y de Sistema (E/S)
    en formatos decimal y exponencial para un análisis comparativo.
    6. Imprime el arreglo ordenado resultante.
    7. Libera los recursos de memoria y finaliza el programa.
*/

int main(int argc, char *argv[])
{
    int i, n, *A;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

    if (argc != 2)
    {
        printf("Usage: %s <number of elements>\n", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);
    A = malloc(n * sizeof(int));

    if (A == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    uswtime(&utime0, &stime0, &wtime0);

    algoritmo_shell(n, A);

    uswtime(&utime1, &stime1, &wtime1);

    // Cálculo del tiempo de ejecución del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    // Mostrar los tiempos en formato exponecial
    printf("\n");
    printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    free(A);
    return 0;
}

/*
void algoritmo_shell(int n, int *A);
DESCRIPCION: Función que utiliza el algoritmo de ordenamiento de Shell para ordenar un arreglo.
RECIBE: Un entero que indica el tamaño del arreglo y una dirección de memoria (puntero al arreglo).
DEVUELVE: void (No retorna valor explícito)
OBSERVACIONES: Ordena los valores del arreglo A de tamaño n utilizando intervalos (gaps) decrecientes
para comparar y mover elementos distantes, mejorando el rendimiento respecto al método de inserción directa.
Su complejidad promedio se encuentra entre O(n log n) y O(n^2), dependiendo de la secuencia de intervalos utilizada.
*/

void algoritmo_shell(int n, int *A)
{
    int i, j, k, b, temp;

    // Inicializa el intervalo k a la mitad del tamaño del arreglo
    k = trunc(n / 2);

    while (k >= 1) // Mientras el intervalo sea al menos 1
    {
        b = 1; // Se activa la bandera para entrar al bucle interno

        while (b != 0) // Repite mientras haya intercambios en una pasada
        {
            b = 0; // Reinicia la bandera antes de cada pasada

            // Recorre el arreglo desde el índice k hasta el final
            for (i = k; i <= n - 1; i++)
            {
                // Compara el elemento actual con el que está a una distancia k atrás
                if (A[i - k] > A[i])
                {
                    // Intercambia los elementos si están en el orden incorrecto
                    temp = A[i];
                    A[i] = A[i - k];
                    A[i - k] = temp;

                    // Indica que hubo al menos un intercambio
                    b = b + 1;
                }
            }
        }

        // Reduce el intervalo a la mitad y repite el proceso
        k = trunc(k / 2);
    }
}