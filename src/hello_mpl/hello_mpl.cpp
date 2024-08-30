#include <iostream>
#include <mpl/mpl.hpp>

int main() {
    // Initialize MPL communicator
    const mpl::communicator &comm_world = mpl::environment::comm_world();

    // Get the rank (ID) of the process
    int rank = comm_world.rank();

    // Get the total number of processes
    int size = comm_world.size();

    // Print Hello World from each process
    std::cout << "Hello, World from process " << rank << " out of " << size << " processes!" << std::endl;

    return 0;
}

