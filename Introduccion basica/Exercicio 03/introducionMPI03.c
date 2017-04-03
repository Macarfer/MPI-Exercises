#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE "-I'm a message!-"
#define TAG 99
int main(int argc, char const *argv[]) {
  char * receivedMessage = NULL;
  receivedMessage = (char*) malloc(sizeof(char)*strlen(MESSAGE));
  double startTime=.0,endTime=.0;

  MPI_Init(&argc,&argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD,&world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);\

/*Round robin starting in proccess 0
  - Commented prints are in that way so they don't interfere with time measurements
*/
  if(!world_rank){
    startTime=MPI_Wtime();
    MPI_Send(MESSAGE,strlen(MESSAGE)+1,MPI_CHAR,(world_rank+1)%world_size,TAG,MPI_COMM_WORLD);
    // fprintf(stdout,"I, processor %d out of %d processors have sended a message to %d!\n",world_rank,world_size,(world_rank+1)%world_size);
    MPI_Recv(receivedMessage,strlen(MESSAGE)+1,MPI_CHAR,world_size-1,TAG,MPI_COMM_WORLD,NULL);
    endTime=MPI_Wtime();
    fprintf(stdout,"Total elapsed time: %e s\n",endTime-startTime);
    fflush(stdout);
    // fprintf(stdout,"I, processor %d out of %d processors have received the following message: \"%s\" from %d\n",world_rank,world_size,receivedMessage,world_size-1);
  }else{
      MPI_Recv(receivedMessage,strlen(MESSAGE)+1,MPI_CHAR,(world_rank-1)%world_size,TAG,MPI_COMM_WORLD,NULL);
      // fprintf(stdout,"I, processor %d out of %d processors have received the following message: \"%s\" from %d\n",world_rank,world_size,receivedMessage,(world_rank-1)%world_size);
      MPI_Send(MESSAGE,strlen(MESSAGE)+1,MPI_CHAR,(world_rank+1)%world_size,TAG,MPI_COMM_WORLD);
      // fprintf(stdout,"I, processor %d out of %d processors have sended a message to %d!\n",world_rank,world_size,(world_rank+1)%world_size);
  };
  MPI_Finalize();
  return 0;
}
