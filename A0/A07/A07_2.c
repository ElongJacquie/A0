#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

void print_usage();
int main(int argc, char *argv[])
{
    int opt;
    char* date_str = NULL;
    struct tm date_tm = {0};
    time_t date_time;
    char weekday[10];

    while((opt = getopt(argc,argv,"t:")) != -1){
        switch(opt){
      case 't':
          date_str = optarg;
          break;
      default:
          print_usage();
          exit(EXIT_FAILURE);
        }
    }

    if(date_str == NULL){
        print_usage();
        exit(EXIT_FAILURE);
    }

    struct tm min_tm1 = {0};
    struct tm min_tm2 = {0};


    strptime("1900-01-01","%Y-%m-%d",&min_tm2);
    if(difftime(mktime(&date_tm),mktime(&min_tm2)) < 0){
        fprintf(stderr,"Date must be after 1900-01-01.\n");
         exit(EXIT_FAILURE);
    }

    date_time = mktime(&date_tm);
    strftime(weekday,sizeof(weekday),"%A",&date_tm);

    printf("The day of the week for %s is %s.\n",date_str,weekday);

    return 0;
}

void print_usage(){
   printf("Usage: ./a07_2 -t YYYY-MM-DD\n");
}

