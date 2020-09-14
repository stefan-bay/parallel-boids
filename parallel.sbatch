#!/bin/bash

# Job settings
#SBATCH --nodes=1
#SBATCH --time=0:10:00
#SBATCH --output=runs/parallel.out

echo "-----------"
echo "OpenMP runs"
echo "-----------"

BOIDS="100"
SECS="20"

export OMP_NUM_THREADS=1
FILE="runs/${OMP_NUM_THREADS}c_parallel_${BOIDS}b_${SECS}s.dat"
echo $OMP_NUM_THREADS core:
./boids_parallel simulate $FILE $BOIDS $SECS
LINEC=$(wc -l $FILE | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

export OMP_NUM_THREADS=2
FILE="runs/${OMP_NUM_THREADS}c_parallel_${BOIDS}b_${SECS}s.dat"
echo $OMP_NUM_THREADS core:
./boids_parallel simulate $FILE $BOIDS $SECS
LINEC=$(wc -l $FILE | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

export OMP_NUM_THREADS=4
FILE="runs/${OMP_NUM_THREADS}c_parallel_${BOIDS}b_${SECS}s.dat"
echo $OMP_NUM_THREADS core:
./boids_parallel simulate $FILE $BOIDS $SECS
LINEC=$(wc -l $FILE | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

export OMP_NUM_THREADS=8
FILE="runs/${OMP_NUM_THREADS}c_parallel_${BOIDS}b_${SECS}s.dat"
echo $OMP_NUM_THREADS core:
./boids_parallel simulate $FILE $BOIDS $SECS
LINEC=$(wc -l $FILE | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

export OMP_NUM_THREADS=16
FILE="runs/${OMP_NUM_THREADS}c_parallel_${BOIDS}b_${SECS}s.dat"
echo $OMP_NUM_THREADS core:
./boids_parallel simulate $FILE $BOIDS $SECS
LINEC=$(wc -l $FILE | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo


export OMP_NUM_THREADS=32
FILE="runs/${OMP_NUM_THREADS}c_parallel_${BOIDS}b_${SECS}s.dat"
echo $OMP_NUM_THREADS core:
./boids_parallel simulate $FILE $BOIDS $SECS
LINEC=$(wc -l $FILE | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo
