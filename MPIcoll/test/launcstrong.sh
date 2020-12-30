#---------launcstrong-----------
#!/bin/bash

#direttive SBATCH
#SBATCH --account=...
#SBATCH --partition=skl_usr_dbg
#SBATCH -t 00:05:00

#env variables and module
module load autoload intelmpi

#execution line
for j in {1..3}
        do
	       srun ./matila 2000 >> strong.out
        done