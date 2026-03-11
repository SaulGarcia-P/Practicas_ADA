/*
Implementacion del algoritmo de ordenamiento por mezcla
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

Descripcion: Programa que implementa un algortimo de ordanamiento por mezcla
para un arreglo de numeros enteros de un tamanio determinado

Compilacion:
Windows: gcc mezcla.c -o mezcla.exe
Linux/Mac: gcc mezcla.c -o mezcla

*/
#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

void MergeSort(int *A, int p, int r);    // Prototipo de funcion. Recibe int * direccion del arreglo A, int p incio del arreglo, int r final del arreglo.
void Merge(int *A, int p, int q, int r); // Protitpo de fncion. Recibe int * direccion del arreglo A, int p inicio del arreglo, int q mitad del arreglo, int r final del arreglo.

/*
int main(int argc, char *argv[])
Recibe: argc   - El número de argumentos pasados por la línea de comandos.
        *argv[] - El vector de argumentos (argv[1] contiene el tamaño 'n').
Devuelve: int (0 si el programa finaliza correctamente).
Función: 
    1. Procesa los argumentos de entrada para determinar el tamaño del arreglo 'n'.
    2. Reserva un bloque de memoria dinámica para 'n' números enteros.
    3. Carga los datos desde la entrada estándar (stdin) hacia el arreglo 'A'.
    4. Implementa el cronometraje de alta precisión mediante la función 'uswtime' 
    para medir el desempeño del algoritmo MergeSort (recursivo).
    5. Calcula y despliega estadísticas de rendimiento: tiempo Real, de Usuario (CPU) 
    y de Sistema (E/S), presentándolos en formato decimal y exponencial.
    6. Realiza la limpieza de recursos mediante la liberación de memoria (free).
*/

int main(int argc, char *argv[])
{
    // Variables para la medición de tiempos
    double utime0, stime0, wtime0, utime1, stime1, wtime1;

    // Variables para el algoritmo
    int i, p, n, *A;
    p = 0;

    // Recibir por argumento el tamanio de n
    if (argc != 2)
    {
        printf("\nIndique el tamanio de n. Ejemplo %s 100\n", argv[0]);
        exit(1);
    }
    // Tomar el tamanio de n por los argumentos del main
    n = atoi(argv[1]);

    // Apartar espacio de memoria para A
    A = malloc(n * sizeof(int));
    if (A == NULL)
    {
        printf("\nError al intentar reservar memoria para %d elementos\n", n);
        exit(1);
    }
    // Leer la entreda de los n valores y colocarlos en un arreglo de numeros
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

   // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    // Llamar al algoritmo
    MergeSort(A, p, n - 1);

    // Evaluar los tiempos de ejecución
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
    //******************************************************************

    // Enviar a la salida estandar el arreglo final
    //for (i = 0; i < n; i++)
    //    printf("\nA[%d]=%d", i, A[i]);

    free(A); // Liberar memoria

    return 0;
}

/*
void MergeSort(int *A, int p, int r);
Descripcion: Ordena los elementos de un arreglo de tamanio n.
Recibe: int * direccion de un arreglo A, int p indice incial del arreglo, int r indice final del arreglo
Devuelve: void (No retorna valor explicito).
Observaciones: Observaciones: Funcion que ordena los valores del arreglo A de tamanio n
en razon de O(nlog(n))
*/
void MergeSort(int *A, int p, int r)
{
    int q;
    // Verifica que el índice inicial sea menor que el final (caso base de la recursión)
    if (p < r)
    {
        // Calcula el punto medio del subarreglo
        q = (p + r) / 2;
        // Llamadas recursivas para ordenar la primera mitad del arreglo
        MergeSort(A, p, q);
        // Llamadas recursivas para ordenar la segunda mitad del arreglo
        MergeSort(A, q + 1, r);
        // Combina ambas mitades ordenadas en un solo subarreglo ordenado
        Merge(A, p, q, r);
    }
}
/*
void Merge(int *A, int p, int q, int r);
Descripcion: Ordena los elementos de un arreglo de tamanio n.
Recibe: int * direccion de un arreglo A, int p indice incial del arreglo, int r indice final del arreglo, int q indice de mitad del arreglo
Devuelve: void (No retorna valor explicito).
Observaciones: Observaciones: Funcion que ordena los valores del arreglo A de tamanio n
en razon de O(nlog(n))
*/
void Merge(int *A, int p, int q, int r)
{
    // Declaración de variables
    int l, i, j, k, *C;
    // Calcula el tamaño del subarreglo temporal
    l = r - p + 1;
    // Inicializa índices para recorrer las dos mitades del arreglo
    i = p;
    j = q + 1;
    // Reserva memoria para el arreglo auxiliar C
    C = malloc(l * sizeof(int));
    if (C == NULL)
    {
        printf("Error al intentar reservar memoria para %d elementos. ", l);
        exit(1);
    }
    // Fusión de los dos subarreglos en C
    for (k = 0; k <= l; k++)
    {
        if (i <= q && j <= r)
        {
            // Compara los elementos de ambas mitades y almacena el menor en C
            if (A[i] < A[j])
            {
                C[k] = A[i];
                i++;
            }
            else
            {
                C[k] = A[j];
                j++;
            }
        }
        // Si quedan elementos en la primera mitad, los copia a C
        else if (i <= q)
        {
            C[k] = A[i];
            i++;
        }
        // Si quedan elementos en la segunda mitad, los copia a C
        else
        {
            C[k] = A[j];
            j++;
        }
    }
    // Copia los elementos ordenados de C de vuelta al arreglo original A
    k = p;
    for (i = 0; i < l; i++)
    {
        A[k] = C[i];
        k++;
    }
    // Libera la memoria reservada para C
    free(C);
}