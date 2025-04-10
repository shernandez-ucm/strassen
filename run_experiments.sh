#!/bin/bash

for item in 512 1024 2048 4096
do
    echo "---------------------------------------"
    echo “Iterativo n : $item”
    ./iterativo $item
    echo "---------------------------------------"
    echo “Iterativo OpenMP n : $item”
    ./iterativo_openmp $item
    echo "---------------------------------------"
    echo “Recursivo n : $item”
    ./recursivo $item
    echo "---------------------------------------"
    echo “Recursivo Threaded n : $item”
    ./recursivo_threaded $item
done