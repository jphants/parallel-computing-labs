package main

import (
	"fmt"
	"time"
)

const MAX = 100
const BLOCK_SIZE = 10 // Tamaño del bloque

var A, B, C [MAX][MAX]float64

func main() {
	// Inicializar matrices A y B
	for i := 0; i < MAX; i++ {
		for j := 0; j < MAX; j++ {
			A[i][j] = float64(i+j) * 0.5
			B[i][j] = float64(i-j) * 0.3
			C[i][j] = 0
		}
	}

	// Medir tiempo de multiplicación de matrices por bloques
	start := time.Now()

	for bi := 0; bi < MAX; bi += BLOCK_SIZE {
		for bj := 0; bj < MAX; bj += BLOCK_SIZE {
			for bk := 0; bk < MAX; bk += BLOCK_SIZE {
				// Multiplicación dentro de los bloques
				for i := bi; i < bi+BLOCK_SIZE && i < MAX; i++ {
					for j := bj; j < bj+BLOCK_SIZE && j < MAX; j++ {
						for k := bk; k < bk+BLOCK_SIZE && k < MAX; k++ {
							C[i][j] += A[i][k] * B[k][j]
						}
					}
				}
			}
		}
	}

	elapsed := time.Since(start)
	fmt.Printf("Tiempo de multiplicación de matrices por bloques: %v\n", elapsed)
}
