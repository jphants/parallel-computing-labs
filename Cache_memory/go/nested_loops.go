package main

import (
	"encoding/csv"
	"fmt"
	"os"
	"time"
)

func rowMajorAccess(A [][]float64, N int, csvFile *csv.Writer) {
	start := time.Now()

	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			temp := A[i][j] // Evitar optimización del compilador
			_ = temp
		}
	}

	elapsed := time.Since(start).Seconds()
	fmt.Printf("N = %d | Row-major: %f s\n", N, elapsed)
	csvFile.Write([]string{fmt.Sprintf("%d", N), fmt.Sprintf("%f", elapsed)})
}

func columnMajorAccess(A [][]float64, N int, csvFile *csv.Writer) {
	start := time.Now()

	for j := 0; j < N; j++ {
		for i := 0; i < N; i++ {
			temp := A[i][j] // Evitar optimización del compilador
			_ = temp
		}
	}

	elapsed := time.Since(start).Seconds()
	fmt.Printf("N = %d | Column-major: %f s\n", N, elapsed)
	csvFile.Write([]string{"", fmt.Sprintf("%f", elapsed)})
}

func main() {
	file, err := os.Create("nested_loops.csv")
	if err != nil {
		fmt.Println("Error al crear el archivo CSV:", err)
		return
	}
	defer file.Close()

	csvWriter := csv.NewWriter(file)
	defer csvWriter.Flush()

	csvWriter.Write([]string{"Dimension", "Row-major", "Column-major"})

	for N := 4000; N <= 5000; N += 50 {
		A := make([][]float64, N)
		for i := range A {
			A[i] = make([]float64, N)
			for j := range A[i] {
				A[i][j] = float64(i+j) * 0.5
			}
		}

		rowMajorAccess(A, N, csvWriter)
		columnMajorAccess(A, N, csvWriter)
		fmt.Println("----------------------")
	}

	fmt.Println("Resultados guardados en 'nested_loops.csv'")
}
