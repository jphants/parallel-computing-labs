#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

void run_experiment(int N, ofstream &csv_file) {
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

    // Medir tiempo de multiplicación de matrices clásica
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {      // Row-major
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Escribir resultados en el archivo CSV
    csv_file << N << "," << elapsed.count() << endl;

    // Mostrar en consola
    cout << "N = " << N << " | Tiempo: " << elapsed.count() << " s" << endl;
}

int main() {
    ofstream csv_file("matrix_classic.csv");
    csv_file << "Dimension,Tiempo\n"; // Encabezado del CSV

    int sizes[] = {10, 50, 100, 200, 500}; // Diferentes tamaños de matriz

    for (int N : sizes) {
        run_experiment(N, csv_file);
    }

    csv_file.close();
    cout << "Resultados guardados en 'matrix_classic.csv'\n";
    return 0;
}
