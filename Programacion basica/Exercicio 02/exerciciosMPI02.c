#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "read_data.h"
#include <mpi.h>
#include <math.h>
// Tempo aprox 0.017
int entrySetSize;
int numberOfThreads;
#define readEntrySetSize 2048
#define pathToMatrixA "./A.txt"
#define pathToVectorB "./b.txt"
#define ROOT_PROCESS 0
#define MATRIX_TAG 98
#define VECTOR_TAG 99

void calculateProduct(int argc,char *argv[]);

int main(int argc, char *argv[]){
  double finalTime;

  #ifndef entrySetSize
    #define entrySetSize strtol(argv[1], NULL, 10)
  #endif
  // numberOfThreads=strtol(argv[1], NULL, 10);

  // finalTime=
  calculateProduct(argc,argv);
  // printf("%lf\n",finalTime);
  // fprintf(stderr,"%lf\n",finalTime);
  return 0;
}


void calculateProduct(int argc, char *argv[]){
  double *matrixA=NULL,*vectorB=NULL, * solution;
  int i = 0, j = 0,tid;
  double sum = 0.0,startTime=.0,endTime=.0;
  /*
      Initialize data!
  */
  solution = (double *) malloc(entrySetSize*sizeof(double));
  matrixA = (double *) malloc(entrySetSize*entrySetSize*sizeof(double));
  vectorB = (double *) malloc(entrySetSize*sizeof(double));
  if(entrySetSize==readEntrySetSize){
    matrixA = importDOUBLE(pathToMatrixA,entrySetSize,entrySetSize);
    vectorB = importDOUBLE(pathToVectorB,entrySetSize,1);
  }else{
    for(i=0;i<entrySetSize;i++){
      for(j=0;j<entrySetSize;j++){
          *(matrixA+i*entrySetSize+j)=rand();
      }
          *(vectorB+i)=rand();
    }
  }

  /************************************************************************************************************
  *                                                                                                           *
  *                                             Compute section                                               *
  *                                                                                                           *
  *************************************************************************************************************/
  MPI_Init(&argc,&argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD,&world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);



  double *localMatrix = (double *)malloc(entrySetSize*entrySetSize*sizeof(double)/world_size);
  double *localSolution = (double*)malloc(entrySetSize*sizeof(double)/world_size);
  int dimension = entrySetSize/world_size;

  startTime=MPI_Wtime();
  MPI_Scatter(matrixA,entrySetSize*dimension,MPI_DOUBLE,localMatrix,entrySetSize*dimension,MPI_DOUBLE,ROOT_PROCESS,MPI_COMM_WORLD);
  MPI_Bcast(vectorB,entrySetSize,MPI_DOUBLE,ROOT_PROCESS,MPI_COMM_WORLD);

  for(i=world_rank*dimension;i<(world_rank+1)*dimension;i++){
      for(j=0;j<entrySetSize;j+=4){
        *(localSolution+i%dimension)+=*(localMatrix+(i%dimension)*entrySetSize+j)**(vectorB+j);
          *(localSolution+i%dimension)+=*(localMatrix+(i%dimension)*entrySetSize+j+1)**(vectorB+j+1);
            *(localSolution+i%dimension)+=*(localMatrix+(i%dimension)*entrySetSize+j+2)**(vectorB+j+2);
              *(localSolution+i%dimension)+=*(localMatrix+(i%dimension)*entrySetSize+j+3)**(vectorB+j+3);
        }
      }
  MPI_Gather(localSolution,dimension,MPI_DOUBLE,solution,dimension,MPI_DOUBLE,ROOT_PROCESS,MPI_COMM_WORLD);

  endTime=MPI_Wtime();
  MPI_Finalize();
  if(!world_rank){
    fprintf(stderr,"%9le\n",solution[2047]);
    fprintf(stdout,"%lf\n",endTime-startTime);
}
}
