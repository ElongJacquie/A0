#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <csv.h>
#define BUFFER_SIZE 1024

typedef struct {
char **headertabelle;
char ***line;
int number_of_line;
int number_of_columns;
} csv_data;


void cell_funct(void *s , size_t len , void *data);
void line_funct(int s , void *data);
void yug_maj(char *satz);
void yug_min(char *satz);
void print_csv(csv_data *patience , int uppercase , int Lowercase , int filter );


int main(int argc , char *argv[])
{
   FILE *yug = fopen("file_A09.csv" , "r");

   if(!yug){
    perror("fehler beim Oeffen der Datei");
    return(EXIT_FAILURE);
   }
   csv_data patience = {NULL , NULL , -1 , 0};
   struct csv_parser p ;
   csv_init(&p , 0);
   char buffer[BUFFER_SIZE];
   size_t nbytes;

   while(nbytes = fread(buffer , 1 ,BUFFER_SIZE , yug) > 0){
    if(csv_parse(&p , buffer ,nbytes ,cell_funct ,line_funct ,&patience)!= nbytes ){
        fprintf(stderr , "error when pasting file\n");
       return(EXIT_FAILURE);
    }
   }

   csv_fini(&p , cell_funct ,line_funct ,&patience );
   csv_free(&p);
   fclose(yug);
   int uppercase = 0 ,lowercase = 0 , filter = 0 , j ,i ;
   for(i = 1 ; i < argc ; i++){
    if(strcmp(argv[i], "-u") == 0){
        uppercase = 1;
    }
    if(strcmp(argv[i], "-l") == 0){
        lowercase = 1;
    }
    if(strcmp(argv[i], "-f") == 0){
        filter = 1;
    }
   }
   print_csv(&patience , uppercase, lowercase , filter);

   for(i = 0; i< patience.number_of_columns; i++) free(patience.headertabelle[i]);
   for(i = 0; i < patience.number_of_line ; i++){
    for(i = 0; j< patience.number_of_columns; j++) free(patience.line[i][j]);
    free(patience.line[i]);

    }

   free(patience.headertabelle);
   free(patience.line);

   return 0 ;

}
void cell_funct(void *s , size_t len , void *data){
csv_data *patience = (csv_data *)data;
if(patience->number_of_columns < 0){

    patience->headertabelle = realloc(patience->headertabelle , (patience->number_of_columns + 2)*sizeof(char *));
    patience->headertabelle[patience->number_of_columns] = strndup(s , len);
    patience->number_of_columns++;

}
else {

  patience->line[patience->number_of_line] = realloc(patience->line[patience->number_of_line] , (patience->number_of_columns + 1)*sizeof(char *));
  patience->line[patience->number_of_line] [patience->number_of_columns] = strndup(s , len );
}
}

void line_funct(int s , void *data){
csv_data *patience = (csv_data *)data;
if(patience->number_of_columns >= 0){

        patience->number_of_line++;
        patience->line  = realloc(patience->line , patience->number_of_line*sizeof(char **));
        patience->line[patience->number_of_line - 1] = NULL;
        patience->number_of_columns = 0 ;
}
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

void print_csv(csv_data *patience , int uppercase , int Lowercase , int filter ){

    int *co = malloc(patience->number_of_columns*sizeof(int));
    int i; int j;
    for(i = 0; i < patience->number_of_columns; i++){
        co[i = i];
    }
    if(filter){
     for(i = 0; i < patience->number_of_columns-1; i++)
     for(j = i + 1;j < patience->number_of_columns; j++){
      if(strcmp(patience->headertabelle[co[i]] , patience->headertabelle[co[j]]) > 0){
        int temp = co[i];
        co[i] = co[j];
        co[j] = temp;
      }
     }
    }

printf("data:\n");

for(i = 0; i < patience->number_of_columns; i++){
    char *header = patience->headertabelle[co[i]];
    if (uppercase){
        yug_maj(header);
    }
    if(Lowercase){
        yug_min(header);
    }
    printf("%s\t",header);
}
printf("\n");

for(i = 0; i < patience->number_of_line; i++){
    for(j = 0; j< patience->number_of_columns; j++){
        char *p = patience->line[i][co[j]];
        if (uppercase){
        yug_maj(p);
    }
    if(Lowercase){
        yug_min(p);
    }
    printf("%s\t",p);
    }
    printf("\n");
}
free(co);
}

