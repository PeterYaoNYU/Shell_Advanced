#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utility.h"

void siginit(struct sigaction * def, sigset_t * mask, void (*handler)(int)){
    struct sigaction new;

    sigemptyset(&(def->sa_mask));
    sigemptyset(&(new.sa_mask));
    sigemptyset(mask);

    def->sa_flags = 0;
    new.sa_flags = 0;

    sigaddset(&(new.sa_mask), SIGINT);
    sigaddset(&(new.sa_mask), SIGQUIT);
    sigaddset(&(def->sa_mask), SIGQUIT);
    sigaddset(&(def->sa_mask), SIGINT);

    sigaddset(mask, SIGINT);
    sigaddset(mask, SIGQUIT);

    def->sa_handler = SIG_DFL;
    new.sa_handler = handler;

    sigaction(SIGINT, &new, NULL);
    sigaction(SIGQUIT, &new, NULL);
}

// int main(){
//     struct sigaction dfl;
//     sigset_t mask;
//     siginit(&dfl, &mask, NULL);
// }