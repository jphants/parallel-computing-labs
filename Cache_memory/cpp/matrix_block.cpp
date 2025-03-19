#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

void run_experiment(int N, int BLOCK_SIZE, ofstream &csv_file) {
    vector<vector<double>> A(N, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(N));
    vector<vector<double>> C(N, vector<double>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) * 0.5;
            B[i][j] = (i - j) * 0.3;
        }
    }

    auto start = chrono::high_resolution_clock::now();

    for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
            for (int bk = 0; bk < N; bk += BLOCK_SIZE) {
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

    csv_file << N << "," << BLOCK_SIZE << "," << elapsed.count() << endl;

    cout << "N = " << N << ", BLOCK_SIZE = " << BLOCK_SIZE << " | Tiempo: " << elapsed.count() << " s" << endl;
}

int main() {
    ofstream csv_file("matrix_block_results.csv");
    csv_file << "Dimension,Tamaño de Bloque,Tiempo\n";

    int sizes[] = {10, 50, 100, 200, 500};
    int block_sizes[] = {16};

    for (int N : sizes) {
        for (int BLOCK_SIZE : block_sizes) {
            run_experiment(N, BLOCK_SIZE, csv_file);
        }
    }

    csv_file.close();
    cout << "Resultados guardados en 'matrix_block_results.csv'\n";
    return 0;
}
