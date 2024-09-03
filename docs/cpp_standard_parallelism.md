# C++ Standard Parallelism

C++ standard parallelism, introduced with the C++17 standard and expanded in
C++20, brings significant benefits by offering a standardized and portable way
to perform parallel computations within the language. This addition allows
developers to leverage the power of multi-core processors directly through the
C++ Standard Library, using well-defined parallel algorithms like
`std::for_each`, `std::reduce`, and `std::transform`. One of the key advantages
of C++ standard parallelism is that it simplifies the development process by
providing a consistent API that abstracts away platform-specific details. This
ensures that code can run across different environments with minimal changes,
which is a stark contrast to the more platform-dependent approaches of using
`pthreads` or OpenMP.

## Benefits of C++ Standard Parallelism

1. **Portability and Consistency:** C++ standard parallelism is designed to
work across different compilers and operating systems, which ensures
portability and consistency. Unlike `pthreads`, which are Unix-specific, or
OpenMP, which requires specific compiler support, C++ standard parallelism uses
the Standard Template Library (STL) constructs, making it inherently portable.
This is beneficial for projects that need to be compiled and run on different
platforms without modification.

2. **Ease of Use:** Standard parallelism in C++ integrates seamlessly with the
existing STL, making it intuitive for developers who are already familiar with
C++ standard libraries. It reduces the learning curve compared to `pthreads`,
where explicit thread management, synchronization, and error handling are
required, or OpenMP, which requires understanding of compiler directives and
pragmas. The high-level abstractions provided by standard parallelism minimize
the risk of common multithreading bugs such as data races and deadlocks.

3. **Performance Optimization:** While OpenMP is a powerful tool for
high-performance computing due to its fine-grained control over parallel
execution, C++ standard parallelism provides a balanced approach by leveraging
the capabilities of underlying hardware through well-optimized library
implementations. Although `pthreads` can be more flexible and powerful for
certain low-level operations, they require more manual optimization and tuning,
which can lead to more complex and less maintainable code. The C++ standard
approach uses execution policies (`std::execution::par`,
`std::execution::par_unseq`) that allow the compiler and runtime to optimize
parallel execution, potentially achieving performance close to or exceeding
that of manually managed threads or OpenMP for many common tasks.

**Contrast with Pthreads and OpenMP:**

- **Pthreads** offer low-level thread control, which is highly powerful but
also complex and error-prone. Developers must manage thread creation,
synchronization (using mutexes, condition variables), and lifecycle, which
increases the potential for bugs. C++ standard parallelism abstracts these
complexities, allowing developers to focus on algorithmic logic rather than
thread management.

- **OpenMP** provides a higher-level interface compared to `pthreads` by using
compiler directives to parallelize loops and sections of code. It offers
scalability and is widely used in scientific and engineering applications.
However, OpenMP requires a preprocessor and compiler that support it, and its
directives can be less flexible when integrating deeply with C++ STL
components. Standard parallelism, being a part of the language standard itself,
naturally integrates with the C++ ecosystem, promoting more modular and
maintainable code. Moreover, while OpenMP focuses on shared-memory parallelism,
the C++ standard parallelism model is flexible enough to be extended for
distributed computing scenarios.

In conclusion, C++ standard parallelism offers a robust, portable, and
easy-to-use alternative to traditional parallel programming models like
`pthreads` and OpenMP. It leverages modern compiler optimizations and
integrates naturally with C++ applications, providing a solid foundation for
both performance and code maintainability.

## Examples

### Hello, World!

Certainly! To write a "Hello, World!" program in C++ that utilizes C++ standard
parallelism, we can use the features provided by the C++17 standard library.
Specifically, we'll use the `<execution>` header, which provides support for
parallel execution policies.

Below is a simple example that demonstrates how to use standard parallelism to
print "Hello, World!" multiple times in parallel:

```{literalinclude} ../src/hello_parallel.cpp
:language: cpp
```

#### Explanation:

1. **Include Headers**: - `<iostream>`: For input-output operations. -
`<vector>`: To use the `std::vector` container. - `<execution>`: To access
execution policies for parallelism. - `<algorithm>`: For using `std::for_each`.

2. **Vector Initialization**: - A vector `data` of size 10 is created and
initialized with zeros. The elements are just placeholders to enable the
iteration.

3. **Parallel Execution**: - `std::for_each`: This algorithm applies a function
to each element in a range. - `std::execution::par`: This execution policy
enables parallel execution of the algorithm. - `data.begin(), data.end()`:
These denote the range of elements in the vector to be processed. - `[](int&) {
... }`: A lambda function that will be executed for each element in the vector.
It simply prints "Hello, World!" to the console.

Note:
- The use of `std::execution::par` ensures that the printing of
"Hello, World!" is attempted in parallel. However, the actual parallelism might
vary depending on the implementation and the system's ability to handle
parallel tasks.
- In a real-world scenario, especially with I/O operations like
printing to the console, actual speedup may not be achieved due to I/O being a
common bottleneck. The primary purpose here is to demonstrate the syntax and
concept.

#### Compilation:

To compile this program, you need to use a C++ compiler that supports C++17.
For example, using `g++`, you can compile the code with:

```bash g++ -std=c++17 -o hello_parallel hello_parallel.cpp
```

Then run the program:

```bash ./hello_parallel
```

This program should print "Hello, World!" ten times, potentially in parallel
depending on the system's threading and execution capabilities.

### Hello, World! with Thread Index

To modify the program to print the thread index alongside "Hello, World!", we
need a way to identify the thread. In a standard parallel execution context
with the C++ Standard Library, directly accessing the thread index isn't part
of the standard library's parallelism features. However, we can use a
combination of thread-local storage and atomic counters to emulate this
behavior.

Here's an updated version of the "Hello, World!" program that also prints the
thread index:

```{literalinclude} ../src/hello_parallel_with_thread_index.cpp
:language: cpp
```

#### Explanation:

1. **Thread Index Management**: - `std::atomic<int> thread_counter{0};`: An
atomic counter is used to assign a unique index to each thread. - `thread_local
int thread_index = thread_counter++;`: This line ensures that each thread gets
a unique index. The `thread_local` specifier ensures that each thread has its
own instance of the `thread_index` variable.

2. **Synchronization for Output**: - `std::mutex print_mutex;`: A mutex is used
to ensure that output to `std::cout` is thread-safe and doesn't get jumbled. -
`std::lock_guard<std::mutex> lock(print_mutex);`: This creates a scoped lock
around the `std::cout` statement, ensuring that only one thread prints at a
time.

3. **Parallel Execution with `std::for_each`**: - The `std::for_each` loop is
executed in parallel using `std::execution::par`. - Each thread gets its own
index via the `thread_index` variable and prints a message to the console.

#### Compilation and Execution:

Compile the program using a C++17-compatible compiler, like `g++`, and then run
it:

```bash
g++ -std=c++17 -o hello_parallel_with_thread_index hello_parallel_with_thread_index.cpp
./hello_parallel_with_thread_index
```

### Expected Output:

The output will look something like this, with the order of lines potentially
varying due to the parallel execution:

```
Hello, World! from thread index: 0
Hello, World! from thread index: 1
Hello, World! from thread index: 2
...
```

Each "Hello, World!" line will be accompanied by a thread index, demonstrating
the use of multiple threads in parallel. The actual number of lines and the
indices may vary based on the system and the runtime environment's handling of
parallel execution.

### Parallel Matrix-Matrix Multiplication

To perform matrix-matrix multiplication using C++ standard parallelism, we can
utilize features from the C++17 standard, such as `std::for_each` with a
parallel execution policy from the `<execution>` header. Below is a C++ program
that demonstrates matrix-matrix multiplication using standard parallelism.

```{literalinclude} ../src/matrix_multiplication_parallel.cpp
:language: cpp
```

#### Explanation:

1. **Matrix Representation**: - The matrices are represented using the `Matrix`
type, which is a `std::vector` of `std::vector<int>`. This structure represents
a 2D matrix.

2. **Matrix Initialization**: - The `initializeMatrix` function initializes a
given matrix with a specific number of rows, columns, and a default value. In
this example, it initializes all elements of matrix `A` to `1` and all elements
of matrix `B` to `2`.

3. **Matrix Multiplication**: - The `multiplyMatrices` function performs matrix
multiplication. It takes two matrices `A` and `B` as input and computes their
product matrix `C`. - The function uses `std::for_each` with
`std::execution::par` to enable parallel processing of rows. The lambda
function inside `std::for_each` computes the dot product for each element in
the resulting matrix `C`.

4. **Matrix Printing**: - The `printMatrix` function prints the contents of a
matrix to the console.

5. **Main Function**: - In the `main` function, two matrices `A` and `B` are
initialized. Matrix multiplication is performed using the `multiplyMatrices`
function, and the result is printed.

#### Compilation and Execution

To compile and run the program, you need a C++17-compatible compiler like
`g++`. Use the following commands:

```bash
g++ -std=c++17 -o matrix_multiplication_parallel matrix_multiplication_parallel.cpp
./matrix_multiplication_parallel
```

#### Expected Output

The output of the program will look like this:

```
Matrix A:
1 1 1 
1 1 1 
1 1 1 
Matrix B:
2 2 2 
2 2 2 
2 2 2 
Result Matrix C (A x B):
6 6 6 
6 6 6 
6 6 6 
```

#### Notes:

- The program performs matrix multiplication in parallel using the execution
policy `std::execution::par`. This parallelization can improve performance on
multi-core systems.
- Ensure that the matrices are compatible for multiplication (i.e., the number
of columns in `A` should equal the number of rows in `B`).
- The order of rows processed in parallel may vary due to the nature of
parallel execution, but the result will be consistent for a given input.

