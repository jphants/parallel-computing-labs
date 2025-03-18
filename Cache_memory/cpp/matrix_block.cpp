#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

void run_experiment(int N, int BLOCK_SIZE, ofstream &csv_file) {
    // Usar vectores dinámicos en el heap para evitar stack overflow
    vector<vector<double>> A(N, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(N));
    vector<vector<double>> C(N, vector<double>(N, 0)); // Inicializar con ceros

    // Inicializar matrices A y B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) * 0.5;
            B[i][j] = (i - j) * 0.3;
        }
    }

    // Medir tiempo de multiplicación de matrices por bloques
    auto start = chrono::high_resolution_clock::now();

    for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
            for (int bk = 0; bk < N; bk += BLOCK_SIZE) {
                // Multiplicación dentro de los bloques
                for (int i = bi; i < min(bi + BLOCK_SIZE, N); i++) {
                    for (int j = bj; j < min(bj + BLOCK_SIZE, N); j++) {
                        for (int k = bk; k < min(bk + BLOCK_SIZE, N); k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Escribir resultados en el archivo CSV
    csv_file << N << "," << BLOCK_SIZE << "," << elapsed.count() << endl;

    // Mostrar en consola
    cout << "N = " << N << ", BLOCK_SIZE = " << BLOCK_SIZE << " | Tiempo: " << elapsed.count() << " s" << endl;
}

int main() {
    ofstream csv_file("matrix_block.csv");
    csv_file << "Dimension,Tamaño de Bloque,Tiempo\n";

    int sizes[] = {10, 50, 100, 200, 500};
    int block_sizes[] = {10};

    for (int N : sizes) {
        for (int BLOCK_SIZE : block_sizes) {
            run_experiment(N, BLOCK_SIZE, csv_file);
        }
    }

    csv_file.close();
    cout << "Resultados guardados en 'matrix_block.csv'\n";
    return 0;
}
