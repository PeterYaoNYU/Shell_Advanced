#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include "utility.h"


#define MAX_BUF 1024
#define PROMPT "> "

int main(int argc, char * argv[]) {
    char inbuf[MAX_BUF];
    // printf("running shell");
    
    for( ; ; ){
        memset(inbuf, 0, MAX_BUF);
        fputs(PROMPT, stdout);
        fgets(inbuf, MAX_BUF, stdin);

        int len;
        len = strlen(inbuf);
        if (inbuf[len-1] == '\n'){
            inbuf[len-1] = '\0';
        }
        pid_t child_pid = fork();
        if (child_pid == 0){
            // printf("in child");
            char ** argvp;
            int count = makeargv(inbuf, " ", &argvp);
            for (int i = 0; i < count ; i++){
                printf("%s\n", argvp[i]);
            }
            printf("executing...\n");
            execvp(argvp[0], argvp);
        } else {
            wait(NULL);
        }
    }
    // printf("%s\n", inbuf);
}