/*
Implementacion del algortimo de ordenamiento de seleccion
Autores: 
		Garcia Peñalva Saul 
		López Alvarado Daniel
		Olarte Tomas Kevin Saul
Autor original: 
		Edgardo Adri­an Franco Martinez
Fecha de entrega 11 de Marzo del 2025
Version: 2.0

Descripcion: Programa que implementa un algorimto de ordenamiento por seleccion
para un arreglo de numeros enteros de tamanio determinado.

Compilacion:
windows: gcc seleccion.c -o seleccion.exe
linux/mac: gcc seleccion.c -o seleccion

Ejecucion:
    ./seleccion {tamanio de arreglo a ordenar} < lista_de_numeros.txt
    ./seleccion {tamanio de arreglo a ordenar} < lista_de_numeros.txt > salida.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

void Seleccion(int *A, int n); // Prototipo de funcion. Recibe int * direccion del arreglo A, int n tamanio del arreglo.

/*
int main(int argc, char *argv[])
Recibe: argc   - El número de argumentos pasados por la línea de comandos.
        *argv[] - El vector de argumentos (donde argv[1] es el tamaño 'n').
Devuelve: int (0 si el programa finaliza correctamente).
Función: 
    1. Procesa los parámetros de entrada para definir el tamaño del conjunto de datos.
    2. Reserva un bloque de memoria dinámica para alojar 'n' números enteros.
    3. Llena el arreglo mediante la lectura de valores desde la entrada estándar.
    4. Ejecuta el algoritmo 'Seleccion', evaluando su desempeño mediante 'uswtime'.
    5. Imprime un reporte detallado de tiempos (Real, CPU, E/S) en formato decimal 
    y científico para facilitar el análisis de complejidad.
    6. Libera la memoria utilizada para mantener la integridad de los recursos del sistema.
*/

int main(int argc, char *argv[])
{
    // Variables para la medición de tiempos
    double utime0, stime0, wtime0, utime1, stime1, wtime1;

    // Variables para el algoritmo
    int i, n, *A;

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
    Seleccion(A, n);

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
void Seleccion(int *A, int n);
Descricion: Ordena los elemenotos de un arreglo A de tamanio n.
Recibe: int * direccion de un arreglo A, int n tamanio del arreglo.
Devuelve: void (No retorna valor explicito).
Observaciones: Observaciones: Funcion que ordena los valores del arreglo A de tamanio n
en razon de O(n^2)
*/
void Seleccion(int *A, int n)
{
    // Declaracion de variables
    int k, i, p, temp;
    // Se inicia el bucle que recorre todo el arreglo desde el elemento 0 hasta el elemento n-2
    for (k = 0; k <= (n - 2); k++)
    {
        // En cada iteracion, se asigna a 'p' el valor actual de 'k' (p es el elemento menor relativo a la iteracion)
        p = k;
        // Se inicializa el bucle que recorre todos los elementos desde el valor actual de 'k'+1 hasta 'n-1'
        for (i = k + 1; i <= (n - 1); i++)
        {
            // Verifica si el elemento 'i(k+1)' es menor al anterior 'p(k)'
            if (A[i] < A[p])
            {
                // Se asigna 'p' como el valor como el valor de 'i'
                p = i;
            }
        }
        // Se asigna a la variable temporal el valor de p
        temp = A[p];
        // Se intercambia el valor de k a la posicion de 'p'
        A[p] = A[k];
        // Se asigna a la posicion 'k' el elemento menor relativo a la iteracion
        A[k] = temp;
    }
}