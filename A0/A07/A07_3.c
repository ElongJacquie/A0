#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int zellers_congruence(int day, int month, int year);
const char* get_weekday(int day, int month, int year);

int main(int argc, char *argv[])
{
    int opt;
    char* date_str = NULL;
    int day, month, year;

    while((opt = getopt(argc,argv,"t:")) != -1){
        switch(opt){
      case 't':
          date_str = optarg;
          break;
      default:
          fprintf(stderr,"Usage: ./weekday -t YYYY-MM-DD\n");
          exit(EXIT_FAILURE);
        }
    }

    if(date_str == NULL || sscanf(date_str,"%d-%d-%d",&year,&month,&day) != 3){
         fprintf(stderr,"Invalid date format. Expected YYYY-MM-DD\n");
        exit(EXIT_FAILURE);
    }
    const char * weekday = get_weekday(day,month,year);
    printf("The day of the week for %s is %s.\n",date_str,weekday);
return 0;
}



int zellers_congruence(int day, int month, int year){

   int begin_year, end_year, result;

   if(month == 1 ){
     month = 13;
     year--;
   }

   if(month == 2 ){
     month = 14;
     year--;
   }

   begin_year = year / 100;
   end_yrar = year - (begin_year*100);

   result = day+(2.6*(month+1))+(begin_year/4)+(5*begin_year+end_year)+(end_year/4);

   return result%7;
}

const char* get_weekday(int day, int month, int year){
   const char* weekdays[]={"Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};
   return weekdays[zellers_congruence(day, month, year)];
}

