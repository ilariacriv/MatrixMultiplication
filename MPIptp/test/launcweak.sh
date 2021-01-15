#---------launcweak-----------
#!/bin/bash

#direttive SBATCH
#SBATCH --account= ...
#SBATCH --partition=skl_usr_dbg
#SBATCH -t 00:05:00
#SBATCH -o output.out

#env variables and module
module load autoload intelmpi

#execution line
for j in {1..10}
        do
	       srun ./mat $1 >> weak.out
        done
