#!/bin/sh
#SBATCH -J ana-danzer-computer-vision
#SBATCH -p skl
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH -o %x_%j.out
#SBATCH -e %x_%j.err
#SBATCH --time=12:00:00
#SBATCH --comment etc
#SBATCH --exclusive

export OMP_NUM_THREADS=1

module purge
module load gcc/8.3.0


./ana-danzer -i ../Danzer/tracefile_computer-vision.txt -o ./resultfile_computer-vision.txt
