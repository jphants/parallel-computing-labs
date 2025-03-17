#include <iostream>
#include <chrono>

#define MAX 100

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main() {
    // Inicializar matrices A y B
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = (i + j) * 0.5;
            B[i][j] = (i - j) * 0.3;
            C[i][j] = 0;
        }
    }

    // Medir tiempo de multiplicación de matrices clásica
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < MAX; i++) {      // Row-major
        for (int j = 0; j < MAX; j++) {
            for (int k = 0; k < MAX; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de multiplicación de matrices clásica: " << elapsed.count() << " segundos\n";

    return 0;
}
