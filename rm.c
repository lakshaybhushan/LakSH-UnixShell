#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define RED "\e[0;31m"
#define RESET "\e[0m"

int rm(char **argv){
  struct stat st = {0};
  if (stat(argv[1], &st) == -1) {
    printf(RED "lakSH: %s: No such file or directory\n" RESET, argv[1]);
    return 1;
  }
  else{
    unlink(argv[1]);
    }
 return 1;

}

int rmr(char **argv){
  struct stat st = {0};
  if (stat(argv[2], &st) == -1) {
    printf(RED "lakSH: %s: No such file or directory\n" RESET, argv[2]);
    return 1;
  }
  else{
    remove(argv[2]);
  }

 return 1;

}

int rmv(char **argv){

  struct stat st = {0};
  if (stat(argv[2], &st) == -1) {
    printf(RED "lakSH: %s: No such file or directory\n" RESET, argv[2]);
    return 1;
  }
  else{
    if (unlink(argv[2]) == 0) 
      printf("File named %s has been deleted successfully!!\n", argv[2]); 
    else
      printf("Unable to delete the file\n"); 
  }

 return 1;

}

int main (int argc, char *argv[]) {

    if(argc==2) {
        rm(argv); 
    }
    else if(!strcmp(argv[1],"-v")){
        rmv(argv);
    }
    else if(!strcmp(argv[1],"-r")){
        rmr(argv);
    }
    else{
        printf(RED "lakSH: %s: No such file or directory\n" RESET, argv[1]);
    }

    return 0;
}