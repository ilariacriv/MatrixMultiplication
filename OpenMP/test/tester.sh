#!/bin/bash

sbatch ./launcweak.sh 
sbatch ./launchstrong.sh $1
sbatch ./launchseq.sh


