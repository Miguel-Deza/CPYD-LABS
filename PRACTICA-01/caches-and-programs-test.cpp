#include <iostream>
#include <vector>
#include <ctime>

const int MAX = 10000;

int main() {
    std::vector<std::vector<double>> A(MAX, std::vector<double>(MAX, 1.0));
    std::vector<double> x(MAX, 2.0);
    std::vector<double> y(MAX, 0.0);
    int i, j;

    // Mide el tiempo antes de ejecutar el primer par de bucles
    clock_t start_time1 = clock();

    // Primer par de bucles
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    // Mide el tiempo después de ejecutar el primer par de bucles
    clock_t end_time1 = clock();

    // Calcula el tiempo transcurrido en el primer par de bucles
    double elapsed_time1 = static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC;

    // Reinicializa y en 0
    std::fill(y.begin(), y.end(), 0.0);

    // Mide el tiempo antes de ejecutar el segundo par de bucles
    clock_t start_time2 = clock();

    // Segundo par de bucles
    for (j = 0; j < MAX; j++) {
        for (i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }

    // Mide el tiempo después de ejecutar el segundo par de bucles
    clock_t end_time2 = clock();

    // Calcula el tiempo transcurrido en el segundo par de bucles
    double elapsed_time2 = static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC;

    // Imprime los tiempos de ejecución
    std::cout << "Tiempo para el primer par de bucles: " << elapsed_time1 << " segundos" << std::endl;
    std::cout << "Tiempo para el segundo par de bucles: " << elapsed_time2 << " segundos" << std::endl;

    return 0;
}
