#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>

int main() {
    // Create a vector of 10 elements, each initialized to 0
    std::vector<int> data(10, 0);

    // Use std::for_each with a parallel execution policy to print "Hello, World!"
    std::for_each(std::execution::par, data.begin(), data.end(), [](int&) {
        std::cout << "Hello, World!" << std::endl;
    });

    return 0;
}

