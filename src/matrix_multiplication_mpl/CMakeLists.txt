cmake_minimum_required(VERSION 3.14)
project(HelloMPLMPI LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find MPI
find_package(MPI REQUIRED)

# Use FetchContent to download MPL if not available
include(FetchContent)

FetchContent_Declare(
    MPL
    GIT_REPOSITORY https://github.com/rabauke/mpl.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(MPL)

# Add the executable
add_executable(matrix_multiplication matrix_multiplication.cpp)

# Include MPL headers
target_include_directories(matrix_multiplication PRIVATE ${mpl_SOURCE_DIR})

# Link against MPI
target_link_libraries(matrix_multiplication PRIVATE MPI::MPI_CXX)

