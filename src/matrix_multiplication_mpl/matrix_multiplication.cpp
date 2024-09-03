#include <iostream>
#include <vector>
#include <mpl/mpl.hpp>

void print_matrix(const std::vector<std::vector<int>> &matrix, const std::string &name) {
    std::cout << name << ":\n";
    for (const auto &row : matrix) {
        for (const auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    const mpl::communicator &comm_world = mpl::environment::comm_world();
    int rank = comm_world.rank();
    int size = comm_world.size();

    const int N = 4;  // Size of the matrix (N x N)
    std::vector<std::vector<int>> A(N, std::vector<int>(N));
    std::vector<std::vector<int>> B(N, std::vector<int>(N));
    std::vector<std::vector<int>> C(N, std::vector<int>(N, 0)); // Result matrix

    if (rank == 0) {
        // Initialize matrices A and B
        int value = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                A[i][j] = value;
                B[i][j] = value;
                value++;
            }
        }

        print_matrix(A, "Matrix A");
        print_matrix(B, "Matrix B");
    }

    // Broadcast matrix B to all processes
    comm_world.bcast(0, B);

    // Determine the number of rows each process will handle
    int rows_per_process = N / size;
    int remaining_rows = N % size;

    int start_row = rank * rows_per_process;
    int end_row = (rank + 1) * rows_per_process;

    if (rank == size - 1) {
        end_row += remaining_rows;  // Last process may handle extra rows
    }

    // Each process computes its part of matrix C
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Gather results from all processes to process 0
    if (rank == 0) {
        std::vector<std::vector<int>> full_C(N, std::vector<int>(N));
        comm_world.gather(0, C.data(), full_C.data(), 0);
        print_matrix(full_C, "Result Matrix C");
    } else {
        comm_world.gather(0, C.data(), 0);
    }

    return 0;
}

