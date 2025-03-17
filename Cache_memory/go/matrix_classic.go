package main

import (
	"fmt"
	"time"
)

const MAX = 100

var A, B, C [MAX][MAX]float64

func matrix_classic() {
	// Inicializar matrices A y B
	for i := 0; i < MAX; i++ {
		for j := 0; j < MAX; j++ {
			A[i][j] = float64(i+j) * 0.5
			B[i][j] = float64(i-j) * 0.3
			C[i][j] = 0
		}
	}

	// Medir tiempo de multiplicación de matrices clásica
	start := time.Now()

	for i := 0; i < MAX; i++ { // Row-major
		for j := 0; j < MAX; j++ {
			for k := 0; k < MAX; k++ {
				C[i][j] += A[i][k] * B[k][j]
			}
		}
	}

	elapsed := time.Since(start)
	fmt.Printf("Tiempo de multiplicación de matrices clásica: %v\n", elapsed)
}
