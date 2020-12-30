NxN Matrix multiplication in MPI with Send anc Recv

Given dim=N

Compile with SLURM: 
module load autoload intelmpi
mpiicc -std=c99 matriciMPIptp.c -o mat

Execute with SLURM: sbatch ./launcher_mpi.sh <matrix dim>
Output will be in output.out

Tests: 

Execute: ./tester.sh <dim>

This script will schedule and execute all the test for weak and strong scalability.
dim should be the dimension to use for the strong scalability.

Each time is calculated 3 times, you should modify the scripts with more iteration in order to have higher accuracy.

Time calculation for strong scalbility will be in: strong.out
Time calculation for weak scalbility will be in: weak.out
Time calculation for sequential resolution will be in: seq.out