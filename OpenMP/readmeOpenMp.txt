NxN Matrix multiplication in OpenMp

Given dim the matrix dimension

Compile: gcc -fopenmp matrixopenMP.c -o mat
Execute with SLURM: sbatch ./launcher_openmp.sh <number of process> <dim>

Tests: 

Execute: ./tester.sh <dim>

This script will schedule all the test for weak and strong scalability.
dim should be the dimension you want to test for the strong scalability.

Each test is calculated 10 times, you should calculate the average 

Time calculation output for strong scalbility will be in: strong.out
Time calculation output for weak scalbility will be in: weak.out
Time calculation output for sequential resolution will be in: seq.out