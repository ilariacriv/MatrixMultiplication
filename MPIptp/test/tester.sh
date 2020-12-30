#!/bin/bash

for i in 1 2 4 
 for j in 1 2 
    do
        t=$(($i*$j))
      	n=$(($t*$i*100))
  	    sbatch --nodes $i --ntasks-per-node $t ./launcweak.sh $n
        sbatch --nodes $i --ntasks-per-node 1 ./launcseq.sh $n
done

sbatch --nodes 1 --ntasks-per-node 1 ./launcstrong.sh $1
sbatch --nodes 1 --ntasks-per-node 2 ./launcstrong.sh $1
sbatch --nodes 2 --ntasks-per-node 2 ./launcstrong.sh $1
sbatch --nodes 2 --ntasks-per-node 4 ./launcstrong.sh $1
sbatch --nodes 4 --ntasks-per-node 4 ./launcstrong.sh $1
sbatch --nodes 4 --ntasks-per-node 8 ./launcstrong.sh $1
sbatch --nodes 4 --ntasks-per-node 16 ./launcstrong.sh $1
sbatch --nodes 4 --ntasks-per-node 32 ./launcstrong.sh $1