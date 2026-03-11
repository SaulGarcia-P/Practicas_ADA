/*
IMPLEMENTACION DEL ALGORITMO RAPIDO PARA ORDENAR UN CONJUNTO DE ELEMENTOS
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

DESCRIPCION: Este codigo ordena un arreglo de n elementos de menor a mayor utilizando el algoritmo rápido. El algoritmo
rápido o Quick Sort es un algoritmo de ordenamiento basado en la técnica de divide y vencerás. Su funcionamiento comienza
con la selección de un pivote, un elemento del arreglo que se utiliza para dividir el arreglo en dos partes. Luego, el
algoritmo reorganiza el arreglo de tal manera que todos los elementos menores que el pivote se ubiquen a su izquierda y
los elementos mayores a su derecha. Después de esta reorganización, el pivote se encuentra en su posición final, es decir,
en la posición que tendría en un arreglo completamente ordenado.

OBSERVACIONES: El tamanio del arreglo debe ser un numero entero positivo.

COMPILACION PARA GENERAR EL CODIGO:

Windows: gcc shell.c tiempo.c -o shell
Linux: gcc shell.c tiempo.c -o shell

EJECUCION:
    rapido.exe tamanio_arreglo < numeros10millones.txt > salida_rapido.txt
*/
// LIBRERIAS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tiempo.h"

void QuickSort(int *arr, int p, int r);
int Pivot(int *arr, int p, int r);
void Intercambiar(int *arr, int i, int j);

/*
int main(int num_arg, char *argv[])
Recibe: num_arg - Número de argumentos recibidos (incluyendo el nombre del programa).
        *argv[]  - Vector de cadenas (argv[1] representa la cantidad de datos 'num_ing').
Devuelve: int (0 si el programa finaliza correctamente).
Función: 
    1. Valida y convierte el argumento de entrada para determinar el tamaño del arreglo.
    2. Gestiona la memoria dinámica mediante 'malloc' para almacenar 'num_ing' enteros.
    3. Carga el arreglo con datos provenientes de la entrada estándar.
    4. Implementa el cronometraje con 'uswtime' para medir el rendimiento de 'QuickSort'.
    5. Calcula y reporta el tiempo Real, de Usuario (CPU) y de Sistema (E/S) en 
    formatos de punto flotante y notación científica.
    6. Libera la memoria reservada y finaliza el proceso.
*/

int main(int num_arg, char *argv[])
{

    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

    int i, j, num_ing, *arr;

    if (num_arg != 2)
    {
        exit(1);
    }

    num_ing = atoi(argv[1]);
    if (num_ing <= 0)
    {
        exit(1);
    }

    arr = malloc(num_ing * sizeof(int));
    if (arr == NULL)
    {
        printf("\nError al intentar reservar memoria para %d elementos\n", num_ing);
        exit(1);
    }

    for (i = 0; i < num_ing; i++)
    {
        scanf("%d", &arr[i]);
    }

    uswtime(&utime0, &stime0, &wtime0); // Guarda el tiempo antes de ordenar.

    QuickSort(arr, 0, num_ing - 1);

    uswtime(&utime1, &stime1, &wtime1); // Guarda el tiempo después de ordenar.

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

    // for (j = 0; j < num_ing; j++)
    //{
    //     printf("%d\n", arr[j]);
    // }

    free(arr);
    return 0;
}

/*
void QuickSort(int *arr, int p, int r);
DESCRIPCION: Funcion que divide el arreglo en subarreglos más pequeños alrededor de un pivote y luego ordena esos
subarreglos de manera recursiva hasta que todo el arreglo está ordenado.
Devuelve: void (No retorna valor explicito)
*/

void QuickSort(int *arr, int p, int r)
{
    if (p < r)
    {
        /* Llama a la función Pivot para obtener el índice de partición (posicion final),
        donde el arreglo está parcialmente ordenado.*/
        int j = Pivot(arr, p, r);
        QuickSort(arr, p, j - 1); // Ordena recursivamente la mitad de la izquierda
        QuickSort(arr, j + 1, r); // Ordena recursivamente la mitad de la derecha
    }
}

/*
int Pivot(int *arr, int p, int r)
DESCRIPCION: Función que selecciona el pivote y particiona el arreglo.
Devuelve: Un entero.
*/
int Pivot(int *arr, int p, int r)
{

    int piv = arr[p], i = p + 1, j = r;

    // Recorrer el arreglo desde ambos extremos usando i y j
    // Repite hasta que los índices se crucen.
    while (i <= j)
    {
        while (i <= r && arr[i] <= piv)
        { // Encuentra un número mayor al pivote desde la izquierda.
            i++;
        }
        while (arr[j] > piv)
        { // Encuentra un número menor o igual al pivote desde la derecha.
            j--;
        }
        // Si los indices no se cruzan se intercambia los elementos
        if (i < j)
        {
            Intercambiar(arr, i, j);
        }
    }
    // Cuando se cruzan, se itercambia el pivote con el valor en la posición j para ponerlo en su lugar correcto.
    Intercambiar(arr, p, j);
    return j;
}

/*
void Intercambiar(int *arr, int i, int j);
DESCRIPCION: Función para intercambiar dos elementos en el arreglo
Devuelve: void (No retorna valor explicito)
*/

void Intercambiar(int *arr, int i, int j)
{
    int temp = arr[j];
    arr[j] = arr[i]; // Intercambia el valor en i con el valor en j.
    arr[i] = temp;
}
