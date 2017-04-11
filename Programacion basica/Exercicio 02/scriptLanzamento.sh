#!/bin/sh
#SBATCH -N 1 # solicitamos nodos
#SBATCH -t 00:00:3 # solicitamos segundos de ejecución (mandatory)
srun execucion >> sol.txt
