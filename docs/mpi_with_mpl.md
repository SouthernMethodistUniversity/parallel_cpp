# The Message Passing Library (MPL)

Using the C++ MPL (Message Passing Library) in conjunction with MPI (Message
Passing Interface) provides several significant benefits for developers working
on parallel computing and distributed systems. Here are a few key advantages:

1. **Type Safety and Modern C++ Features:** One of the primary benefits of
using MPL with MPI is the enhanced type safety it offers. MPL is designed with
modern C++ standards in mind, utilizing features such as templates, type
inference, and smart pointers. This helps ensure that message-passing
operations are type-safe, reducing the likelihood of runtime errors due to type
mismatches. The ability to leverage modern C++ features such as lambdas, auto
keyword, and constexpr also allows developers to write more concise and
maintainable code, making use of idiomatic C++ patterns that are both robust
and easier to understand.

2. **Improved Abstraction and Usability:** MPL provides a higher-level
abstraction over the traditional MPI C/C++ bindings. By encapsulating common
MPI operations into C++ classes and functions, MPL simplifies the syntax and
reduces boilerplate code, leading to clearer and more readable codebases.
Developers can focus more on the problem they are solving rather than the
intricacies of MPI. This abstraction layer not only makes it easier to perform
common tasks like point-to-point communication, broadcasting, and collective
operations but also allows for the integration of complex C++ data types
seamlessly.

3. **Enhanced Productivity and Reduced Development Time:** By simplifying
MPI's verbose and often error-prone API, MPL significantly reduces the learning
curve for new developers and speeds up the development process for seasoned
programmers. MPL's design encourages best practices by providing a more
intuitive API, which reduces the likelihood of common MPI-related bugs (such as
incorrect buffer sizes, improper type handling, and synchronization issues).
The result is a shorter development cycle, quicker debugging, and faster
time-to-market for scientific and engineering applications that rely on
parallel computing.

4. **Scalability and Performance Optimization:** MPL is optimized to work
efficiently with MPI's underlying communication mechanisms. It takes advantage
of MPI's high-performance, low-latency communication capabilities while
providing additional optimizations that are facilitated by modern C++
compilers. This means that applications developed using MPL can scale
efficiently across large numbers of processors, making it suitable for
high-performance computing (HPC) environments. Additionally, MPL's API is
designed to minimize the overhead introduced by its abstractions, ensuring that
applications can achieve near-native MPI performance.

5. **Portability and Compatibility:** MPL is designed to be fully
compatible with the MPI standard, ensuring that existing MPI-based applications
can be easily ported to use MPL without significant changes to the underlying
code. This backward compatibility makes MPL an attractive option for developers
looking to modernize their codebases while maintaining the ability to run on
various platforms that support MPI. Moreover, MPL's abstraction layer can help
mitigate platform-specific quirks and differences in MPI implementations,
further enhancing portability.

In summary, using the C++ MPL library with MPI provides a combination of modern
C++ features, improved type safety, usability, enhanced productivity, and
performance optimization. These benefits make it a powerful tool for developers
working on parallel computing applications, helping to write more efficient,
maintainable, and scalable code.

## Examples

### Hello, World!

To create a "Hello, World" style program in C++ that utilizes the Message
Passing Interface (MPI) for parallelism with the Message Passing Library (MPL),
you'll first need to ensure that you have MPL set up in your environment. MPL
is a modern C++ wrapper for MPI, which simplifies the process of using MPI by
providing a more C++-like interface.

Here's a simple example of a "Hello, World" program using MPL and MPI:

#### Prerequisites
1. **MPI Library**: You need an MPI implementation such as OpenMPI or MPICH
installed on your system.
2. **MPL**: You need to have MPL installed. MPL is header-only, so you can
include it in your project without a complicated installation process. You can
find it on [MPL GitHub](https://github.com/rabauke/mpl).

:::{tip}
On M3, `module load gcc/11.2.0 openmpi`.
:::

#### Hello World using MPL with MPI

```{literalinclude} ../src/hello_mpl/hello_mpl.cpp
:language: cpp
```

#### Explanation

1. **Including MPL**: `#include <mpl/mpl.hpp>` includes the
MPL header file, which provides the necessary classes and functions to interact
with MPI.
2. **Initialize Communicator**: `const mpl::communicator &comm_world
= mpl::environment::comm_world();` initializes the default communicator
(similar to `MPI_COMM_WORLD` in standard MPI).
3. **Rank and Size**: -
`comm_world.rank()`: This function returns the rank (or ID) of the current
process. - `comm_world.size()`: This function returns the total number of
processes participating in the communicator.
4. **Printing**: Each process
prints its rank and the total number of processes, allowing us to see parallel
execution.

#### Compilation and Execution

To compile and run this program, you typically use an MPI compiler wrapper like
`mpic++`. Additionally you can use CMake to automatically download the
dependencies.

1. **Compile the Program**:
    ```bash
    mpic++ -o hello_mpl hello_mpl.cpp
    ```
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    ```{literalinclude} ../src/hello_mpl/CMakeLists.txt
    :language: cmake
    ```
   

2. **Run the Program**: Specify the number of processes using `mpirun` or `mpiexec`.
    ```bash
    mpirun -np 4 ./hello_mpl
    ```

This command will start 4 processes, and you should see output from each
process indicating its rank.

#### Example Output
If you run the program with 4 processes, you might see something like:

```
Hello, World from process 0 out of 4 processes!
Hello, World from process 1 out of 4 processes!
Hello, World from process 2 out of 4 processes!
Hello, World from process 3 out of 4 processes!
```

#### Notes
- Ensure that the MPL headers are correctly included in your project
path or specified using the include flag during compilation.
- The order of output may vary as processes execute independently.

This simple program demonstrates how to initialize an MPI environment using
MPL, obtain information about each process, and print output in a parallelized
manner.

### Matrix-Matrix Multiplication

To create a C++ program using MPL (Message Passing Library) for MPI-based
parallel matrix-matrix multiplication, we need to distribute the work across
multiple processes. Each process will handle a portion of the matrix
multiplication, and we'll use MPI to manage communication between the
processes.

For simplicity, consider square matrices of size `N x N`. Each process will
compute a part of the result matrix. We'll use row-wise decomposition, where
each process is responsible for a specific set of rows in the result matrix.

#### Steps to Implement the Program:

1. **Distribute the Matrices**: We'll distribute parts of matrices `A` and `B`
among different MPI processes.
2. **Perform Local Computation**: Each process computes its part of the result
matrix `C`.
3. **Gather Results**: Use MPI to gather all parts of the result matrix `C`
from different processes.

#### C++ Code Using MPL for MPI-Based Parallel Matrix-Matrix Multiplication

Here's a C++ program that performs parallel matrix-matrix multiplication using
MPL:

```{literalinclude} ../src/matrix_multiplication_mpl/matrix_multiplication.cpp
:language: cpp
```

#### Key Parts of the Code

1. **Matrix Initialization**: Matrix `A` and `B` are initialized in process 0.
The program uses integer values for simplicity.
2. **Broadcast Matrix `B`**: The matrix `B` is broadcasted from process 0 to
all other processes using `comm_world.bcast(B.data(), B.size(), 0);`. All
processes receive matrix `B`.
3. **Local Computation**: Each process computes its assigned rows of matrix `C`
using the local data.
4. **Gather Results**: The results are gathered to process 0 using
`comm_world.gather()`. The final result matrix `C` is printed by process 0.

#### Compilation and Execution

1. **Compile**:
    ```bash
    mpic++ -o matrix_multiplication matrix_multiplication.cpp
    ```

2. **Run** (with 4 processes, for example):
    ```bash
    mpirun -np 4 ./matrix_multiplication
    ```

#### Notes

- Ensure that MPL is correctly installed and included in the include path.
- Adjust the matrix size `N` and number of processes to fit your system's
capability.
- This code assumes the number of rows (`N`) is divisible by the number of
processes. If `N` is not divisible by `size`, the last process handles the
remaining rows.

