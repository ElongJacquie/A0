#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define PIPE_NAMED "Yug"
#define BUFFER_SIZE 1024


int main()
{

 char buffer[BUFFER_SIZE];
 int j;
 j = open(PIPE_NAMED,O_WRONLY);
 if (j==-1){
    printf("Fehler beim Öffnen der pipe\n");
    return 0;
 }
 printf("geben sie bitte ein text \n");

 while(fgets(buffer,BUFFER_SIZE, stdin)!= NULL){
  write(j,buffer,strlen(buffer) +1);
 }

 close(j);
    return 0;
}
