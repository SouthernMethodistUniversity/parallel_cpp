#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>

using Matrix = std::vector<std::vector<int>>;

// Function to initialize matrices with sample data
void initializeMatrix(Matrix& matrix, int rows, int cols, int value) {
    matrix.resize(rows, std::vector<int>(cols, value));
}

// Function to perform matrix multiplication
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    // Result matrix with dimensions rowsA x colsB
    Matrix C(rowsA, std::vector<int>(colsB, 0));

    // Perform matrix multiplication using parallelism
    std::for_each(std::execution::par, C.begin(), C.end(), [&](std::vector<int>& row) {
        int i = &row - &C[0];  // Calculate the row index
        for (int j = 0; j < colsB; ++j) {
            row[j] = 0;
            for (int k = 0; k < colsA; ++k) {
                row[j] += A[i][k] * B[k][j];
            }
        }
    });

    return C;
}

// Function to print a matrix
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Define dimensions for matrices
    int rowsA = 3, colsA = 3;
    int rowsB = 3, colsB = 3;

    // Initialize matrices
    Matrix A, B;
    initializeMatrix(A, rowsA, colsA, 1);  // Fill A with 1s
    initializeMatrix(B, rowsB, colsB, 2);  // Fill B with 2s

    // Perform matrix multiplication
    Matrix C = multiplyMatrices(A, B);

    // Print the result matrix
    std::cout << "Matrix A:" << std::endl;
    printMatrix(A);

    std::cout << "Matrix B:" << std::endl;
    printMatrix(B);

    std::cout << "Result Matrix C (A x B):" << std::endl;
    printMatrix(C);

    return 0;
}

