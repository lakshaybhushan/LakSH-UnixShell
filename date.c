// Sun Oct 30 15:12:19 IST 2022

#include <time.h>
#include <string.h>
#include <stdio.h>

#define RED "\e[0;31m"
#define RESET "\e[0m"

int date(){
   time_t mytime;
   struct tm *currtime;
   char systime[100];

   time(&mytime);

   currtime = localtime(&mytime);

   strftime(systime,100,"%a %b %d %X %Z %Y", currtime);
   printf("%s\n", systime);
  
   return 0;
}

int dateu(){
   time_t mytime;
   struct tm *currtime;
   char systime[100];

   time(&mytime);

   currtime = gmtime(&mytime);

   strftime(systime,100,"%a %b %d %X %Z %Y", currtime);
   printf("%s\n", systime);
  
   return 0;
}

int dateRfc(){
   time_t mytime;
   struct tm *currtime;
   char systime[100];

   time(&mytime);

   currtime = localtime(&mytime);

   strftime(systime,100,"%a, %d %b %Y %T %z", currtime);
   printf("%s\n", systime);
  
   return 0;
}


int main(int argc, char* argv[]){
    if (argc==1){
        date();
    }
    else if (!strcmp(argv[1],"-u")){
        dateu();
    }
    else if (!strcmp(argv[1],"-R")){
        dateRfc();
    }
    else{
        printf( RED "Invalid argument !!\n");
    }
    return 0;

}