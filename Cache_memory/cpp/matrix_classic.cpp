#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

void run_experiment(int N, ofstream &csv_file) {
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

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    csv_file << N << "," << elapsed.count() << endl;

    cout << "N = " << N << " | Tiempo: " << elapsed.count() << " s" << endl;
}

int main() {
    ofstream csv_file("matrix_classic_results.csv");
    csv_file << "Dimension,Tiempo\n";

    int sizes[] = {10, 50, 100, 200, 500};

    for (int N : sizes) {
        run_experiment(N, csv_file);
    }

    csv_file.close();
    cout << "Resultados guardados en 'matrix_classic_results.csv'\n";
    return 0;
}
