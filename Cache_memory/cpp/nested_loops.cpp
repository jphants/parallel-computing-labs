#include <iostream>
#include <chrono>

using namespace std;

#define MAX 100

double A[MAX][MAX], x[MAX], y[MAX];

int main() {
    for (int i = 0; i < MAX; i++) {
        x[i] = i + 1;
        y[i] = 0;
        for (int j = 0; j < MAX; j++) {
            A[i][j] = (i + j) * 0.5;
        }
    }

    // Acceso en orden por filas (Row-major)
    auto start1 = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < MAX; i++) {  
        for (int j = 0; j < MAX; j++) {  
            y[i] += A[i][j] * x[j];  
        }  
    }
    
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed1 = end1 - start1;
    cout << "Tiempo del primer par de bucles (Row-major): " << elapsed1.count() << " segundos\n";

    for (int i = 0; i < MAX; i++) {
        y[i] = 0;
    }

    // Acceso en orden por columnas (Column-major)
    auto start2 = chrono::high_resolution_clock::now();
    
    for (int j = 0; j < MAX; j++) {  
        for (int i = 0; i < MAX; i++) {  
            y[i] += A[i][j] * x[j];  
        }  
    }
    
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed2 = end2 - start2;
    cout << "Tiempo del segundo par de bucles (Column-major): " << elapsed2.count() << " segundos\n";

    return 0;
}
