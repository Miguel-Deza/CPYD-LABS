#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace chrono;

// Función para multiplicar matrices clásicamente (tres bucles anidados)
void multiplyMatricesClassic(int** A, int** B, int** C, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Función para multiplicar matrices por bloques (seis bucles anidados)
void multiplyMatricesBlocked(int** A, int** B, int** C, int rowsA, int colsA, int colsB, int blockSize) {
    for (int i = 0; i < rowsA; i += blockSize) {
        for (int j = 0; j < colsB; j += blockSize) {
            for (int k = 0; k < colsA; k += blockSize) {
                for (int ii = i; ii < min(i + blockSize, rowsA); ++ii) {
                    for (int jj = j; jj < min(j + blockSize, colsB); ++jj) {
                        for (int kk = k; kk < min(k + blockSize, colsA); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int sizes[] = {100, 200, 500, 1000};  // Tamaños de las matrices
    int blockSize = 32;  // Tamaño del bloque para la multiplicación por bloques

    for (int size : sizes) {
        // Crear matrices A, B y C como matrices dinámicas de punteros a punteros
        int** A = new int*[size];
        int** B = new int*[size];
        int** C = new int*[size];
        for (int i = 0; i < size; ++i) {
            A[i] = new int[size];
            B[i] = new int[size];
            C[i] = new int[size];
        }

        // Inicializar matrices A y B con valores aleatorios
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                A[i][j] = rand() % 100;  // Números aleatorios entre 0 y 99
                B[i][j] = rand() % 100;
            }
        }

        // Medir el tiempo de ejecución para la multiplicación clásica
        auto start_time_classic = high_resolution_clock::now();
        multiplyMatricesClassic(A, B, C, size, size, size);
        auto end_time_classic = high_resolution_clock::now();
        auto duration_classic = duration_cast<milliseconds>(end_time_classic - start_time_classic);

        // Medir el tiempo de ejecución para la multiplicación por bloques
        auto start_time_blocked = high_resolution_clock::now();
        multiplyMatricesBlocked(A, B, C, size, size, size, blockSize);
        auto end_time_blocked = high_resolution_clock::now();
        auto duration_blocked = duration_cast<milliseconds>(end_time_blocked - start_time_blocked);

        cout << "Tamaño de la matriz: " << size << "x" << size << endl;
        cout << "Tiempo de ejecución (Clásico): " << duration_classic.count() << " ms" << endl;
        cout << "Tiempo de ejecución (Bloques, bloque de tamaño " << blockSize << "): " << duration_blocked.count() << " ms" << endl;
        cout << "-----------------------------------------------------" << endl;

        // Liberar memoria de las matrices
        for (int i = 0; i < size; ++i) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }

    return 0;
}
