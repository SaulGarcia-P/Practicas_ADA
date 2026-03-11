/*
Implementacion código de ordenamiento con Heap (montículo)
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

Descripción: Implementación del algoritmo de ordenamiento HeapSort (montículo) en C.
El programa lee una lista de números enteros desde la entrada estándar, los almacena en un
arreglo, y luego los ordena utilizando el algoritmo HeapSort.

Observación: El usuario debe proporcionar un arreglo de números enteros y su tamaño.

Compilación: gcc HeapSort.c -o HeapSort
*/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

// PROTOTIPO DE FUNCIONES
void HeapSort(int *A, int n);
void InsertHeaP(int *Heap, int *A, int indice);
int Extraer(int *Heap, int HeapSize);

/*
int main(int num_args, char *cadena_args[])
Recibe: num_args     - Número de argumentos pasados por consola.
        *cadena_args - Arreglo de cadenas con los parámetros (ej. nombre del programa y n).
Devuelve: int (0 si el proceso termina con éxito).
Función: 
    1. Valida la entrada del tamaño 'n' desde la línea de comandos.
    2. Asigna memoria dinámica para un arreglo de 'n' enteros.
    3. Carga el arreglo mediante la lectura de datos desde la entrada estándar.
    4. Ejecuta el algoritmo 'HeapSort', midiendo con precisión el tiempo de 
    procesamiento (CPU), tiempo de sistema (E/S) y tiempo real (Wall clock).
    5. Imprime el arreglo ordenado y genera un reporte de rendimiento detallado 
    tanto en formato decimal como exponencial.
    6. Libera los recursos del sistema y finaliza la ejecución.
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

    // Lee de la entrada estandar los n valores y los coloca en un arreglo
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    HeapSort(A, n);
    for(i=0; i<n; i++){
        printf("%d ", A[i]);
    }

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

    // Terminar programa normalmente

    exit(0);
    free(A);

    return 0;
}

// DECLARACIÓN DE FUNCIONES

/*
void HeapSort(int *A, int n);
Descripción: Implementa el algoritmo de ordenamiento HeapSort.
Recibe: int *A y int n (Arreglo de números enteros y su tamaño
Devuelve:
Observaciones: El usuario debe proporcionar un arreglo de números enteros y su tamaño.
*/
void HeapSort(int *A, int n)
{
    // Declaración de variables
    int *Heap, HeapSize;
    int i;

    // Apartar memoria para el heap
    Heap = malloc((n + 1) * sizeof(int));
    if (Heap == NULL)
    {
        printf("\nError al intentar reservar memoria para %d elementos\n", n);
        exit(1);
    }

    // Construir el heap insertando cada elemento del arreglo
    for (i = 0; i < n; i++)
    {
        InsertHeaP(Heap, A, i);
    }

    // Extraer los elementos del heap y colocarlos en el arreglo ordenado
    for (i = 0; i < n; i++)
    {
        HeapSize = n - i; // Actualizar el tamaño del heap
        A[i] = Extraer(Heap, HeapSize);
    }

    // Liberar la memoria del heap
    free(Heap);
}

/*
InsertHeaP(Heap, A, i);
Descripción: Inserta un elemento en el heap.
Recibe: int *Heap, int *A, int indice (Referencia al heap, arreglo original y el índice del elemento a insertar)
Devuelve:
Observaciones: El usuario debe proporcionar el heap, el arreglo original y el índice del elemento a insertar.
*/

void InsertHeaP(int *Heap, int *A, int indice)
{
    // Declaración de variables
    int i, temp;
    // Inicializar variables

    i = indice + 1;      // Ajustar índice para el heap (1-based index)
    Heap[i] = A[indice]; // Insertar el nuevo elemento al final del heap

    // Reorganizar el heap en forma ascendente
    while (i > 1 && Heap[i / 2] > Heap[i])
    {
        // Intercambiar si el padre es menor que el hijo
        temp = Heap[i];
        Heap[i] = Heap[i / 2];
        Heap[i / 2] = temp;
        i = i / 2; // Moverse al índice del padre
        /*
        A = {7,4,1}
        indice = 0
        i = 1
        Heap[1] = 7
        Heap = {_,7}
        i > 1 False

        indice = 1
        i = 2
        Heap[2] = 4
        Heap = {_,7,4}
        i > 1 True
        Heap[1] > Heap[2] True
        7 > 4 True
        temp = 4
        Heap[2] = 7
        Heap[1] = 4
        i = 2/2 = 1
        i > 1 False

        indice = 2
        i = 2 + 1 = 3
        Heap[3] = 1
        i > 1 True
        Heap[3/2=1] > Heap[3]
        4 > 1 True
        temp = 1
        Heap[3] = 4
        Heap[1] = 1
        i = 3/2 = 1
        i > 1 False
        Heap = {_,1,7,4}

         */
    }
}

/*
int Extraer(int *Heap);
Descripción: Extrae el elemento mínimo del heap.
Recibe: int *Heap (Referencia al heap)
Devuelve: int (El elemento mínimo extraído del heap)
Observaciones: El usuario debe proporcionar el heap.
*/
int Extraer(int *Heap, int HeapSize)
{
    // Declaración de variables
    int i, temp, minimo, ultimo;

    // Inicializar variables
    minimo = Heap[1];            // El elemento mínimo está en la raíz del heap
    ultimo = Heap[HeapSize];     // Último elemento del heap
    Heap[1] = ultimo;            // Mover el último elemento a la raíz
    i = 1;                       // Comenzar desde la raíz

    // Reorganizar el heap en forma ascendente
    while (1)
    {
        int izq, der, chiquito;
        izq = 2 * i;     // Índice del hijo izquierdo
        der = 2 * i + 1; // Índice del hijo derecho
        chiquito = i;    // Índice del nodo más pequeño

        // Comparar con el hijo izquierdo
        if (izq <= HeapSize && Heap[izq] < Heap[chiquito])
        {
            chiquito = izq;
        }

        // Comparar con el hijo derecho
        if (der <= HeapSize && Heap[der] < Heap[chiquito])
        {
            chiquito = der;
        }

        // Si el nodo más pequeño es el actual, el heap está ordenado
        if (chiquito == i)
        {
            break;
        }

        // Intercambiar con el nodo más pequeño
        temp = Heap[i];
        Heap[i] = Heap[chiquito];
        Heap[chiquito] = temp;
        i = chiquito; // Moverse al índice del nodo más pequeño
    }

    return minimo; // Devolver el elemento mínimo extraído

}
