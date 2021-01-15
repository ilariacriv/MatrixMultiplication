#!/bin/bash

#direttive SBATCH
#SBATCH --account=..
#SBATCH --partition=skl_usr_dbg
#SBATCH -t 00:10:00
#SBATCH --nodes 1
#SBATCH --ntasks-per-node=1
#SBATCH -c 48
#SBATCH -o strong.out
#SBATCH -e err.err

#execution line
for i in 1 2 4 8 12 16 24 32 40 48
do
  	for j in {1..10}
        do
          	srun ./mat $i $1
        done
done


