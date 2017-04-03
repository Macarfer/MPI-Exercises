#!/bin/sh
#SBATCH -N 5 # solicitamos nodos
#SBATCH -c 1 #24
#SBATCH --ntasks-per-node=1
#SBATCH -t 00:00:3 # solicitamos segundos de ejecución (mandatory)
srun execucion >> sol.txt
