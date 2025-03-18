#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

void row_major_access(const vector<vector<double>>& A, int N, ofstream &csv_file) {
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < N; i++) {  
        for (int j = 0; j < N; j++) {  
            volatile double temp = A[i][j]; // Evitar optimización del compilador
        }  
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "N = " << N << " | Row-major: " << elapsed.count() << " s" << endl;
    
    csv_file << N << "," << elapsed.count() << ",";
}

void column_major_access(const vector<vector<double>>& A, int N, ofstream &csv_file) {
    auto start = chrono::high_resolution_clock::now();
    
    for (int j = 0; j < N; j++) {  
        for (int i = 0; i < N; i++) {  
            volatile double temp = A[i][j]; // Evitar optimización del compilador
        }  
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "N = " << N << " | Column-major: " << elapsed.count() << " s" << endl;
    
    csv_file << elapsed.count() << endl;
}

int main() {
    ofstream csv_file("nested_loops.csv");
    csv_file << "Dimension,Row-major,Column-major\n"; // Encabezado

    for (int N = 4000; N <= 5000; N += 50) {
        vector<vector<double>> A(N, vector<double>(N));

        // Llenar la matriz con algunos valores
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = (i + j) * 0.5;
            }
        }

        row_major_access(A, N, csv_file);
        column_major_access(A, N, csv_file);
        cout << "----------------------\n";
    }

    csv_file.close();
    cout << "Resultados guardados en 'nested_loops.csv'\n";

    return 0;
}
