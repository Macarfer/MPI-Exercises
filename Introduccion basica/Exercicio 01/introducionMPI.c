#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE "-I'm a message!-"
#define TAG 99
int main(int argc, char const *argv[]) {
  char * receivedMessage = NULL;
  receivedMessage = (char*) malloc(sizeof(char)*strlen(MESSAGE));
  int i =0;

  MPI_Init(&argc,&argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD,&world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);\

/*If the rank of the proccess is 0, the it sends a messag to each of the remaining proccesses, if not, the proccess waits until it receives a message from any source with any tag set*/
  if(!world_rank){
    for(i=1;i<world_size;i++)
    MPI_Send(MESSAGE,strlen(MESSAGE)+1,MPI_CHAR,i,TAG,MPI_COMM_WORLD);
    fprintf(stdout,"I, processor %d out of %d processors have sended a message!\n",world_rank,world_size);
  }else{
      MPI_Recv(receivedMessage,strlen(MESSAGE)+1,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,NULL);
      fprintf(stdout,"I, processor %d out of %d processors have received the following message: \"%s\"\n",world_rank,world_size,receivedMessage);
  };

  MPI_Finalize();
  return 0;
}
