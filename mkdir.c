#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define RED "\e[0;31m"
#define BLUE "\e[0;34m"
#define RESET "\e[0m"

int mkdirv(int argc , char *argv[]){
    char *filename = argv[2];
    int check = mkdir(filename, 0);
    if(check == -1){
        printf(RED "LakSH: Directory Already Exists!!\n");
    }
    else{
        chmod(filename, 0777);
        printf(BLUE "Directory created successfully!! \"%s\"\n", filename);
    }
    return 0;
}

int mkdiro(int argc , char *argv[]){
    char *filename = argv[1];
    int check = mkdir(filename, 0);
    if(check == -1){
        printf(RED "LakSH: Directory Already Exists!!\n");
    }
    else{
        chmod(filename, 0777);
    }
    return 0;
}

int mkdirm(int argc , char *argv[]){
    char *filename = argv[3];
    int check = mkdir(filename, 0);
    if(check == -1){
        printf(RED "LakSH: Directory Already Exists!!\n");
    }
    else{
        chmod(filename, 0755);
    }
    return 0;
}

int main(int argc, char *argv[]){
    char *filename = argv[1];
    if (argc ==1){
        printf(RED "Atleast one argument is required!!\n" RESET);
    }
    else if (!strcmp(argv[1], "-v")) {
        mkdirv(argc, argv);
    }
    else if (!strcmp(argv[1], "-m") && (!strcmp(argv[2], "755") || !strcmp(argv[2], "0755"))) {
        mkdirm(argc, argv);
    }
    else if (!strcmp (argv[1], "-m")){
        printf("File Mode Error\n");
    }
    else{
        mkdiro(argc, argv);
    }
    return 0;
}