NxN Matrix multiplication in MPI with collectives

Please note that this works only when 'dim' (matrix dimension) is multiple of the number of process involved

Compile with SLURM: 
module load autoload intelmpi
mpiicc -std=c99 matriciMPIcoll.c -o mat

Execute with SLURM: sbatch ./launcher_mpi.sh  <dim>

Tests: 
Execute: ./tester.sh <dim>

This script will schedule all the test for weak and strong scalability.
dim should be the dimension you want to test for the strong scalability.

Each test is calculated 10 times, you should calculate the average 

Time calculation output for strong scalbility will be in: strong.out
Time calculation output for weak scalbility will be in: weak.out
Time calculation output for sequential resolution will be in: seq.out