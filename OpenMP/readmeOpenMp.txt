NxN Matrix multiplication in OpenMp

Given dim=N

Compile: gcc -fopenmp matrixopenMP.c -o mat
Execute with SLURM: sbatch ./launcher_openmp.sh <number of nodes> <matrix dim>

Tests: 

Execute: ./tester.sh <dim>

This script will schedule all the test for weak and strong scalability.
dim should be the dimension to use for the strong scalability.

Each time is calculated 3 times, you should modify the scripts with more iteration in order to have higher accuracy.

Time calculation for strong scalbility will be in: strong.out
Time calculation for weak scalbility will be in: weak.out
Time calculation for sequential resolution will be in: seq.out