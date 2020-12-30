#---------launcseq-----------
#!/bin/bash

#direttive SBATCH
#SBATCH --account= ...
#SBATCH --partition=skl_usr_dbg
#SBATCH -t 00:05:00
#SBATCH --nodes 2
#SBATCH --ntasks-per-node=2
#SBATCH -o output.out

#env variables and module
module load autoload intelmpi

#execution line
srun ./mat $1
       
