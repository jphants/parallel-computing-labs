package main

import (
	"fmt"
	"time"
)

const MAX = 100

var A [MAX][MAX]float64
var x, y [MAX]float64

func main() {
	// Inicializar matrices y vectores
	for i := 0; i < MAX; i++ {
		x[i] = float64(i + 1)
		y[i] = 0
		for j := 0; j < MAX; j++ {
			A[i][j] = float64(i+j) * 0.5
		}
	}

	// Acceso en orden por filas (Row-major)
	start1 := time.Now()
	for i := 0; i < MAX; i++ {
		for j := 0; j < MAX; j++ {
			y[i] += A[i][j] * x[j]
		}
	}
	elapsed1 := time.Since(start1)
	fmt.Printf("Tiempo del primer par de bucles (Row-major): %v\n", elapsed1)

	// Resetear y
	for i := 0; i < MAX; i++ {
		y[i] = 0
	}

	// Acceso en orden por columnas (Column-major)
	start2 := time.Now()
	for j := 0; j < MAX; j++ {
		for i := 0; i < MAX; i++ {
			y[i] += A[i][j] * x[j]
		}
	}
	elapsed2 := time.Since(start2)
	fmt.Printf("Tiempo del segundo par de bucles (Column-major): %v\n", elapsed2)
}
