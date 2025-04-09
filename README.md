# Divide and Conquer for Matrix Multiplication
 
Implementation of Strassen's Algorithm for matrix multiplication using the Eigen library in C++. This implementation works for square matrices of size $2^n \times 2^n$.

## Compilation Instructions:

Ensure you have the Eigen library installed and accessible. Compile the program using a C++ compiler that supports C++11 or later. For example, with g++:

`g++ -O3  -I ../eigen/ src/iterativo.cpp -o iterativo`.

`g++ -O3 -fopenmp -I ../eigen/ src/iterativo_openmp.cpp -o iterativo_openmp`.

`g++ -O3  -I ../eigen/ src/recursivo.cpp -o recursivo`.

`g++ -O3 -pthread -I ../eigen/ src/recursivo_threaded.cpp -o recursivo_threaded`.

