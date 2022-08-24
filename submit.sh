#!/bin/sh
#PBS -V
#PBS -N ana-danzer-ansys
#PBS -q debug
#PBS -A etc
#PBS -l select=1:ncpus=68
#PBS -l walltime=04:00:00
#PBS -m abe
#PBS -M yhcho.raphael@gmail.com

cd $PBS_O_WORKDIR

module purge
module load gcc/8.3.0

./ana-danzer -i /scratch/jklee/dup_sample/tracefiles/4KB-Chunk-Tracefiles/tracefile-abaqus.txt -o result-4kb-abaqus.txt > log-4kb-abaqus.txt
