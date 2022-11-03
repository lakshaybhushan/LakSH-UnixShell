#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>

#define CYAN "\e[0;36m"
#define GREEN "\e[0;32m"
#define RED "\e[0;31m"
#define RESET "\e[0m"

#define lakSH_DELIM " \t\r\n"

int cd(char** args){
  char path[100];
  if(args[1] == NULL){
     chdir(getenv("HOME"));
  }
    else if (!strcmp(args[1],"..")){
      chdir("..");
    }

    else if (!strcmp(args[1],"~")){
      chdir(getenv("HOME"));
    }
      
    else if (!strcmp(args[1],"-")){
        chdir(getenv("OLDPWD"));
    }
  
    else{
      if (args[1] == NULL) {
      fprintf(stderr, RED "lakSH: expected argument to \"cd\"\n");
      return 1;
      }
      else {
     if (chdir(args[1]) != 0) {
      perror(RED "lakSH"); 
      }
    }
  }
  return 0;
}

int pwd(char** args){
  if (args[1] == NULL){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
  }
  else if (!strcmp(args[1], "-L")){
    char* pwdl;
    pwdl = getenv("PWD");
    printf("%s\n", pwdl);
  }
  else if (!strcmp(args[1], "-P")){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n",cwd);
  }

  else{
    printf(RED "lakSH: invalid option !!\n");
  }
  return 0;
}

int echo(char** args){
  if (args[1] == NULL){
    printf("\n");
  }
  else if (!strcmp(args[1], "-n")){
    int i = 2;
    while(args[i] != NULL){
    printf("%s", args[i]);
    i++;
    }
  }

  else if (!strcmp(args[1], "--help")){
    printf("-------- Echo Help Page --------\n");
    printf("NAME:\n");
    printf("  echo - Write arguments to the standard output (stdout).");
    printf("SYNOPSIS:\n");
    printf("  echo [OPTION]... [STRING]...\n");
    printf("DESCRIPTION:\n");
    printf("   Use to write arguments to the standard output.\n");
    printf("   -n     do not output the trailing newline\n");
    printf("   --help displays help and exit\n");
  }

  else{    
    int i = 1;
    while(args[i] != NULL){
    printf("%s ", args[i]);
    i++;
    }
    printf("\n");
    return 1;
  }
return 0;
}

void laksh_launch(char** args){
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    if (execv(args[0],args) == -1) {
      perror(RED "lakSH");
      }
    } 
    else if (pid < 0) {
      perror(RED "lakSH");
    }
    else {
    wait(NULL);
  }
}

void pthread_date(){
  pthread_t thread_id;

    pthread_create(&thread_id, NULL,(void*)system,"date");
    pthread_join(thread_id, NULL);
}

void pthread_dateu(){
  pthread_t thread_id;

    pthread_create(&thread_id, NULL,(void*)system,"date -u");
    pthread_join(thread_id, NULL);
}

void pthread_dater(){
  pthread_t thread_id;

    pthread_create(&thread_id, NULL,(void*)system,"date -R");
    pthread_join(thread_id, NULL);
}

void pthreadDateMain(char **args){
    if (args[1] == NULL){
      pthread_date();
    }
    else if (strcmp(args[1],"-u")==0){
    pthread_dateu();
    }
    else if (strcmp(args[1],"-R")==0){
    pthread_dater();
    }
    else{
      printf(RED "lakSH: invalid option !!\n");
    }
}

void laksh_execute(char **args, char* dir) {

  if (args[0] == NULL)
  return;

  if (strcmp(args[0], "cd") == 0){
      cd(&args[0]);
  }

  else if (strcmp(args[0], "echo") == 0){
      echo(&args[0]);
  }
     
  else if (strcmp(args[0], "pwd") == 0){
      pwd(&args[0]);
  }

  else if (strcmp(args[0],"date&t")==0){
    pthreadDateMain(&args[0]);
  }
  else if(strcmp(args[0],"exit")==0){
    exit(0);
  }
  else{
    strcat(dir, args[0]);
    args[0] = dir;
    laksh_launch(&args[0]);
  }
}

char** laksh_split_line(char *line) {
  int position = 0;
  int no_of_tokens = 64;
  char ** tokens = malloc(sizeof(char *) * no_of_tokens);
  char * token = strtok(line, lakSH_DELIM);
  while (token != NULL){
  tokens[position] = token;
  position++;
  token = strtok(NULL, lakSH_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void mainloop(void){
  char dir[1024];
  char tempdir[1024];

  getcwd(dir, sizeof(dir));
  strcat(dir, "/");
  strcpy(tempdir, dir);
  
  char pointer[1024];
  char **args;
  int status;

  do {
    strcpy(dir, tempdir);
    printf(GREEN "lakSH> " RESET);
    fgets(pointer, sizeof(pointer), stdin);

    args = laksh_split_line(pointer);

    laksh_execute(args, dir);
    
  } while (1);
}

void ascii(){
  
    printf(GREEN "Welcome to\n\n");
    
    printf(GREEN "██╗░░░░░░█████╗░██╗░░██╗░██████╗██╗░░██╗ \n");
    printf("██║░░░░░██╔══██╗██║░██╔╝██╔════╝██║░░██║ \n");
    printf("██║░░░░░███████║█████═╝░╚█████╗░███████║ \n");
    printf("██║░░░░░██╔══██║██╔═██╗░░╚═══██╗██╔══██║ \n");
    printf("███████╗██║░░██║██║░╚██╗██████╔╝██║░░██║ \n");
    printf("╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝ \n");

    printf("\n");


    printf(CYAN "Available Commands: cd, echo, pwd, ls, cat, date, mkdir, rm\n" RESET);

    printf("\n");
}


int main(int argc, char** argv){
        ascii();
        mainloop();
        return 0;
}
