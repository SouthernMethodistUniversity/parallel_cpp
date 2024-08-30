#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>

int main() {
    // Create a vector of 10 elements
    std::vector<int> data(10, 0);

    // Atomic counter for thread index
    std::atomic<int> thread_counter{0};

    // Mutex for safe printing
    std::mutex print_mutex;

    // Use std::for_each with a parallel execution policy
    std::for_each(std::execution::par, data.begin(), data.end(), [&](int&) {
        // Get a unique index for each thread using atomic increment
        thread_local int thread_index = thread_counter++;

        // Lock for safe printing
        std::lock_guard<std::mutex> lock(print_mutex);

        // Print "Hello, World!" with the thread index
        std::cout << "Hello, World! from thread index: " << thread_index << std::endl;
    });

    return 0;
}

