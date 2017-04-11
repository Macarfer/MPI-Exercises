#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAG 99
#define MAX_ITERATIONS 1000000
#define calculatePi(i)  (1/(pow(16,i)))*((4/(8*i+1))-(2/(8*i+4))-(1/(8*i+5))-(1/(8*i+6)))
#define ROOT_PROCESS 0
int main(int argc, char const *argv[]) {
  int i;
  double startTime,endTime;

  MPI_Init(&argc,&argv);

  double localPI=.0;
  double PI=.0;

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD,&world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
  startTime=MPI_Wtime();
/*If the rank of the proccess is 0, the it sends a messag to each of the remaining proccesses, if not, the proccess waits until it receives a message from any source with any tag set*/
  for(i=(world_rank*MAX_ITERATIONS/world_size);i<(world_rank+1)*MAX_ITERATIONS/world_size;i++){
      localPI+=(1./(pow(16,i)))*((4./(8*i+1))-(2./(8*i+4))-(1./(8*i+5))-(1./(8*i+6)));
  }
  MPI_Reduce(&localPI,&PI,1,MPI_DOUBLE,MPI_SUM,ROOT_PROCESS,MPI_COMM_WORLD);
  endTime=MPI_Wtime();
  if(!world_rank){
    printf("Value of pi calculated with %d processes: %e\n",world_size,PI );
    printf("Time spent: %e s\n",endTime-startTime);
  }
  MPI_Finalize();
  return 0;
}
