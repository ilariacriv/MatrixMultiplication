#!/bin/bash

#direttive SBATCH
#SBATCH --account= ...
#SBATCH --partition=skl_usr_dbg
#SBATCH -t 00:10:00
#SBATCH --nodes 1
#SBATCH --ntasks-per-node=1
#SBATCH -c 48
#SBATCH -o weak.out
#SBATCH -e err.err

#execution line
srun ./mat $1 $2
