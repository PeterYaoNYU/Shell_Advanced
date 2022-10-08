#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "utility.h"

#define MAXBUF 1024
#define OUTFILE_FLAG (O_WRONLY|O_CREAT|O_TRUNC)

int parseandredirectin(char cmd[]){
    char * infile;
    if ((infile = strchr(cmd, '<')) == 0){
        return 0;
    }
    // printf("%s\n", infile);
    // if we do not +1 here, the result will be "< infile" !
    infile = strtok(infile+1, " \t");
    // this is for unit test
    // printf("%s\n", infile);
    int infd;
    infd = open(infile, O_RDONLY);
    dup2(infd, STDIN_FILENO);
    return close(infd);
}

int parseandredirectout(char cmd[]){
    // char outbuf[MAXBUF];
    // strcpy(outbuf, cmd);
    char * outfile;
    if ((outfile = strchr(cmd, '>')) == 0){
        return 0;
    }
    // printf("%s\n", outfile);
    int index = (int)(outfile - cmd);
    cmd[index] = 0;
    outfile = strtok(outfile+1, " \t");
    // printf("%s\n", outfile);
    // printf("%s\n", cmd);
    int outfd = open(outfile, OUTFILE_FLAG);
    // printf("%d\n", outfd);
    dup2(outfd, STDOUT_FILENO);
    // printf("everything fine");
    return close(outfd);
}


int main(void){
    char cmd[MAXBUF] = "copy and paste <  hello.py > jesus.js";
    parseandredirectout(cmd);
    // printf("mid check: %s\n", cmd);
    parseandredirectin(cmd);
    return 0;
}

