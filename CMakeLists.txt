cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project (strassen)
find_package(OpenMP)
find_package (Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(EIGEN_ROOT_DIR "../eigen/")

include_directories(
    ${EIGEN_ROOT_DIR}
)

add_executable (iterativo src/iterativo.cpp)
add_executable (iterativo_openmp src/iterativo_openmp.cpp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(iterativo_openmp PUBLIC OpenMP::OpenMP_CXX)
endif()
add_executable (recursivo src/recursivo.cpp)
add_executable (recursivo_threaded src/recursivo_threaded.cpp)
target_link_libraries(recursivo_threaded pthread)