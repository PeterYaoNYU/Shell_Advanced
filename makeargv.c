#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"

int makeargv(char * s, const char * delimiters, char *** argvp){
    // int length = strlen(s);
    int trailing_head_count = strspn(s, delimiters);
    char * snew = s + trailing_head_count;
    int length = strlen(snew);
    char * t = (char*)malloc(length * sizeof(char));
    strcpy(t, snew);

    int arg_count = 0;
    strtok(t, delimiters);
    for (arg_count = 1; strtok(NULL, delimiters) != NULL; arg_count++);

    // printf("finish counting, the number of arguments is %d\n", arg_count);

    // for (int i = 0; i <= arg_count; i++){
    //     *argvp = (char**)malloc(sizeof(char **));
    // }
    // printf("before seg\n");

    *argvp = malloc((arg_count+1)*sizeof(char *));
    // printf("after seg\n");

    strcpy(t, snew);
    **argvp = strtok(t, delimiters);
    for (int i = 1; i < arg_count; i++){
        *((*argvp)+i) = strtok(NULL, delimiters);
    }

    *((*argvp)+arg_count) = NULL;
    return arg_count;
}

int main(){
    char * s = "nyu-shanghai-fuck-covid";
    // char *** argvp = (char***)malloc(sizeof(char **));
    char ** argvp;
    char * deli = "-";
    int arg_count = makeargv(s, deli, &argvp);
    for (int i = 0; i < arg_count; i++){
        printf("%s\n", *(argvp+i));
    }
    
}