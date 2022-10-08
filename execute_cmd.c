#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include "utility.h"

#define DELI " "

int execute_cmd(char *cmd){
    char ** pipelines;
    int fd[2];
    int count = makeargv(cmd, "|", &pipelines);
    int i;
    for (i = 0; i < count-1; i++){
        pipe(fd);
        pid_t child = fork();
        if (child){
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execute_and_redirect(i==0, 0, pipelines[i]);
        } else {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
        }
    }
    execute_and_redirect(i==0, 1, pipelines[i]);
    return 0;
}

void execute_and_redirect(int in, int out, char cmd[]){
    char ** argvp;
    if (out && strchr(cmd, '>')){
        parseandredirectout(cmd);
    }
    if (in && strchr(cmd, '<')){
        parseandredirectin(cmd);
    }
    makeargv(cmd, DELI, &argvp);
    execvp(argvp[0], argvp);
}