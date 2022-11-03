#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CYAN "\e[0;36m"
#define GREEN "\e[0;32m"
#define PURPLE "\e[0;35m"
#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define RESET "\e[0m"


int cat(char** args){

  FILE *myfile;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  myfile = fopen(args[1], "r");

  if (myfile == NULL){
    printf(RED "File not found!!\n");
    return 1;
  }
  while ((read = getline(&line, &len, myfile)) != -1) {
    printf("%s", line);
  }
  fclose(myfile);

  printf("\n");

  return 1;

}

int cate(char** args){

  FILE *myfile;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  myfile = fopen(args[2], "r");

  if (myfile == NULL){
    printf(RED "File not found!!\n");
    return 1;
  }
  while ((read = getline(&line, &len, myfile)) != -1) {
    line[strlen(line)-1] = '\0';
    printf("%s$\n", line);
  }
  fclose(myfile);
  printf("\n");
  return 1;
}

int catn(char** args){

  FILE *myfile;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i=1;
  myfile = fopen(args[2], "r");

  if (myfile == NULL){
    printf(RED "File not found!!\n");
    return 1;
  }

  while ((read = getline(&line, &len, myfile)) != -1) {
    line[strlen(line)-1] = '\0';
    printf("%d %s\n", i,line);
    i++;
  }
  fclose(myfile);

  printf("\n");

  return 1;

}


int main(int argc , char *argv[]){
  if (argc == 1){
    printf("\n");
    }
    else if (!strcmp(argv[1], "-e")){
        cate(argv);
    }
    else if (!strcmp(argv[1], "-n"))
    {
      catn(argv);
    }
    else {
      cat(argv);
    }
    return 0;
}
