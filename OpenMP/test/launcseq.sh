#!/bin/bash

#direttive SBATCH
#SBATCH --account= ...
#SBATCH --partition=skl_usr_dbg
#SBATCH -t 00:15:00
#SBATCH --nodes 1
#SBATCH --ntasks-per-node=1
#SBATCH -c 48
#SBATCH -o seq.out
#SBATCH -e err.err

#execution line
for i in  1 2 4 8 16 32 
do
  	n=$(($i*100))
        for j in {1..10}
        do
          	srun ./mat 1 $n
        done
done

