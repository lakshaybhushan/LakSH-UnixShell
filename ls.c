#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

#define RED "\e[0;31m"
#define RESET "\e[0m"

int lsmain(int argc, char* argv[]){

    struct dirent **dir;
        int directory_scan=scandir(".",&dir,0,alphasort);
        int i=0;
        while(i<directory_scan){
            char* directName;
            directName=dir[i]->d_name;
            if(directName[0]!='.'){
                printf("%s ",directName);
                free(dir[i]);
            }
            i+=1;
        }
        free(dir);
        printf("\n");

    return 0;
}

int lsr(int argc, char* argv[]){
    struct dirent **dir;
    int directory_scan = scandir(".", &dir,NULL,alphasort);
    int i;
    while (directory_scan --) {
        char* directName;
        directName = dir[directory_scan]->d_name;
        if (directName[0]!= '.') {
            printf("%s ", directName);
            free(dir[directory_scan]);
        }
    }

    printf("\n");
        free(dir);
 return 0;
}

int lsa(int argc, char* argv[]){

        struct dirent **dir;
        int directory_scan=scandir(".",&dir,0,alphasort);
        int i=0;
        while(i<directory_scan){
            char* directName;
            directName=dir[i]->d_name;
            printf("%s ",directName);
            free(dir[i]);
            i+=1;
        }
        free(dir);
        printf("\n");
    return 0;
}

int main(int argc, char* argv[]){
    if(argc==1){
        lsmain(argc,argv);
    }
    else if (!strcmp(argv[1],"-a")){
        lsa(argc,argv);
    }
    else if (!strcmp(argv[1],"-r")){
        lsr(argc,argv);
    }
    else{
        printf(RED "Command not supported!!\n" RESET);
    }
    return 0;
}