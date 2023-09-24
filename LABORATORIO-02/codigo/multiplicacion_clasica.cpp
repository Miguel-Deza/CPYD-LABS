#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace chrono;

// Función para multiplicar matrices por bloques
void multiplyMatrices(int **A, int **B, int **C, int rowsA, int colsA, int colsB, int blockSize)
{
    for (int i = 0; i < rowsA; i += blockSize)
    {
        for (int j = 0; j < colsB; j += blockSize)
        {
            for (int k = 0; k < colsA; k += blockSize)
            {
                for (int ii = i; ii < min(i + blockSize, rowsA); ++ii)
                {
                    for (int jj = j; jj < min(j + blockSize, colsB); ++jj)
                    {
                        for (int kk = k; kk < min(k + blockSize, colsA); ++kk)
                        {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    int rowsA, colsA, rowsB, colsB;

    cout << "Ingrese el número de filas y columnas de la matriz A: ";
    cin >> rowsA >> colsA;

    cout << "Ingrese el número de filas y columnas de la matriz B: ";
    cin >> rowsB >> colsB;

    if (colsA != rowsB)
    {
        cout << "La multiplicación de matrices no es posible." << endl;
        return 1;
    }

    int **A = new int *[rowsA];
    int **B = new int *[colsA];
    int **C = new int *[rowsA];

    for (int i = 0; i < rowsA; ++i)
    {
        A[i] = new int[colsA];
        C[i] = new int[colsB];
    }

    for (int i = 0; i < colsA; ++i)
    {
        B[i] = new int[colsB];
    }

    // Rellenar las matrices con elementos aleatorios
    srand(time(nullptr));
    for (int i = 0; i < rowsA; ++i)
    {
        for (int j = 0; j < colsA; ++j)
        {
            A[i][j] = rand() % 100; // Números aleatorios entre 0 y 99
        }
    }

    for (int i = 0; i < colsA; ++i)
    {
        for (int j = 0; j < colsB; ++j)
        {
            B[i][j] = rand() % 100;
        }
    }

    int blockSize;
    cout << "Ingrese el tamaño del bloque: ";
    cin >> blockSize;

    // Realizar la multiplicación de matrices y medir el tiempo de ejecución
    auto start_time = high_resolution_clock::now();
    multiplyMatrices(A, B, C, rowsA, colsA, colsB, blockSize);
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    // Imprimir la matriz resultante
    cout << "Matriz resultante C:" << endl;
    for (int i = 0; i < rowsA; ++i)
    {
        for (int j = 0; j < colsB; ++j)
        {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    // Liberar memoria
    for (int i = 0; i < rowsA; ++i)
    {
        delete[] A[i];
        delete[] C[i];
    }

    for (int i = 0; i < colsA; ++i)
    {
        delete[] B[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
