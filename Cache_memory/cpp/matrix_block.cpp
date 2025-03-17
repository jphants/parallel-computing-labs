#include <iostream>
#include <chrono>

#define MAX 100
#define BLOCK_SIZE 10  // Tamaño del bloque

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

    // Medir tiempo de multiplicación de matrices por bloques
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int bi = 0; bi < MAX; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < MAX; bj += BLOCK_SIZE) {
            for (int bk = 0; bk < MAX; bk += BLOCK_SIZE) {
                // Multiplicación dentro de los bloques
                for (int i = bi; i < bi + BLOCK_SIZE && i < MAX; i++) {
                    for (int j = bj; j < bj + BLOCK_SIZE && j < MAX; j++) {
                        for (int k = bk; k < bk + BLOCK_SIZE && k < MAX; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de multiplicación de matrices por bloques: " << elapsed.count() << " segundos\n";

    return 0;
}
