package main

import (
	"fmt"
	"time"
)

func multiplyClassic(N int) time.Duration {
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

	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			for k := 0; k < N; k++ {
				C[i][j] += A[i][k] * B[k][j]
			}
		}
	}

	return time.Since(start)
}

func main() {
	dimensions := []int{10, 50, 100, 200, 500}

	for _, N := range dimensions {
		elapsed := multiplyClassic(N)
		fmt.Printf("N = %d | Tiempo: %v\n", N, elapsed)
	}
}
