#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define PIPE_NAMED "Yug"
#define BUFFER_SIZE 1024
#include <ctype.h>

void yug_maj(char *satz);
void yug_min(char *satz);

int main(int argc, char *argv[])
{

int opt; int j; char buffer[BUFFER_SIZE];
int maj = 0 ;int min =0;
while((opt = getopt(argc,argv,"ul")) !=-1){

    switch(opt){

  case 'u' :
    maj = 1;
    break;

  case 'l':
    min = 1;
    break;

  default:
    fprintf(stderr, "fehler\n");

    return 0;
    }
}
 j = open(PIPE_NAMED,O_RDONLY);

 while(read(j , buffer , BUFFER_SIZE) > 0 ){
  if(maj){
    yug_maj(buffer);
  }
  if (min) {
    yug_min(buffer);

  }

  printf("text bearbeitet %s\n",buffer);
 }
 close (j);

 return 0 ;

}
void yug_maj(char *satz){

while(*satz){
    *satz= toupper(*satz);
    satz++;
}
}

void yug_min(char *satz){

while(*satz){
    *satz= tolower(*satz);
    satz++;
}
}

