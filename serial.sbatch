#!/bin/bash

# Job settings
#SBATCH --nodes=1
#SBATCH --time=0:10:00
#SBATCH --output=runs/serial.out

echo "-----------"
echo "Serial runs"
echo "-----------"

BOIDS="100"
SECS="20"

FILE="runs/serial_${BOIDS}b_${SECS}s"

./boids_serial simulate $FILE\(0\).dat $BOIDS $SECS
LINEC=$(wc -l $FILE\(0\).dat | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

./boids_serial simulate $FILE\(1\).dat $BOIDS $SECS
LINEC=$(wc -l $FILE\(1\).dat | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

./boids_serial simulate $FILE\(2\).dat $BOIDS $SECS
LINEC=$(wc -l $FILE\(2\).dat | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

./boids_serial simulate $FILE\(3\).dat $BOIDS $SECS
LINEC=$(wc -l $FILE\(3\).dat | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

./boids_serial simulate $FILE\(4\).dat $BOIDS $SECS
LINEC=$(wc -l $FILE\(4\).dat | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo

./boids_serial simulate $FILE\(5\).dat $BOIDS $SECS
LINEC=$(wc -l $FILE\(5\).dat | sed 's/ .*//') # get line count
echo frames: $(($LINEC / $BOIDS))    # number of frames generated
echo
