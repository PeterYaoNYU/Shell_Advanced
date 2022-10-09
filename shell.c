#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include "utility.h"


#define MAX_BUF 1024
#define PROMPT "> "

sigjmp_buf env;
static volatile sig_atomic_t oktojump = 0;

void sig_handler(int signo){
    if (oktojump == 0){
        return;
    }oktojump = 0;
    siglongjmp(env, 1);
}

int main(int argc, char * argv[]) {
    char inbuf[MAX_BUF];
    // printf("running shell");
    
    struct sigaction default_action;
    sigset_t mask;
    siginit(&default_action, &mask, sig_handler);

    // sigsetjmp(env, 1);

    for( ; ; ){
        if (sigsetjmp(env, 1)){
            fputs("\n", stdout);
        }
        oktojump = 1;
        memset(inbuf, 0, MAX_BUF);
        fputs(PROMPT, stdout);
        fgets(inbuf, MAX_BUF, stdin);

        int len;
        len = strlen(inbuf);
        if (inbuf[len-1] == '\n'){
            inbuf[len-1] = '\0';
        }

        if (strcmp(inbuf, "q") == 0){
            break;
        }

        sigprocmask(SIG_BLOCK, &mask, NULL);
        pid_t child_pid = fork();
        if (child_pid == 0){
            sigaction(SIGINT, &default_action, NULL);
            sigaction(SIGQUIT, &default_action, NULL);
            sigprocmask(SIG_UNBLOCK, &mask, NULL);
            execute_cmd(inbuf);
        } else {
            wait(NULL);
            sigprocmask(SIG_UNBLOCK, &mask, NULL);
        }
    }
    // printf("%s\n", inbuf);
    return 0;
}