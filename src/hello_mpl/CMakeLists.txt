cmake_minimum_required(VERSION 3.14)
project(HelloMPLMPI LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 14)
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
add_executable(hello_mpl hello_mpl.cpp)

# Include MPL headers
target_include_directories(hello_mpl PRIVATE ${mpl_SOURCE_DIR}/include)

# Link against MPI
target_link_libraries(hello_mpl PRIVATE MPI::MPI_CXX)

