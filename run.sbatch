#!/bin/bash

# Job settings
#SBATCH --nodes=1
#SBATCH --time=0:00:10
#SBATCH --output=runs/test5_run.out

echo "-----------"
echo "OpenMP runs"
echo "-----------"
export OMP_NUM_THREADS=32
./boids.out simulate runs/test5.dat
