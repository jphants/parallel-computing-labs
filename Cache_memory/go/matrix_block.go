package main

import (
	"fmt"
	"time"
)

const BLOCK_SIZE = 32

func multiplyMatrices(N int) time.Duration {
	A := make([][]float64, N)
	B := make([][]float64, N)
	C := make([][]float64, N)
	for i := range A {
		A[i] = make([]float64, N)
		B[i] = make([]float64, N)
		C[i] = make([]float64, N)
	}

	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			A[i][j] = float64(i+j) * 0.5
			B[i][j] = float64(i-j) * 0.3
		}
	}

	start := time.Now()

	for bi := 0; bi < N; bi += BLOCK_SIZE {
		for bj := 0; bj < N; bj += BLOCK_SIZE {
			for bk := 0; bk < N; bk += BLOCK_SIZE {
				// Multiplicación dentro de los bloques
				for i := bi; i < min(bi+BLOCK_SIZE, N); i++ {
					for j := bj; j < min(bj+BLOCK_SIZE, N); j++ {
						for k := bk; k < min(bk+BLOCK_SIZE, N); k++ {
							C[i][j] += A[i][k] * B[k][j]
						}
					}
				}
			}
		}
	}

	return time.Since(start)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	dimensions := []int{10, 50, 100, 200, 500}

	for _, N := range dimensions {
		elapsed := multiplyMatrices(N)
		fmt.Printf("N = %d, BLOCK_SIZE = %d | Tiempo: %v\n", N, BLOCK_SIZE, elapsed)
	}
}
