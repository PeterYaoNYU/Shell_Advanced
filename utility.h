int makeargv(char * s, const char * delimiters, char *** argvp);
int parseandredirectin(char cmd[]);
int parseandredirectout(char cmd[]);
void execute_and_redirect(int in, int out, char cmd[]);
int execute_cmd(char *cmd);
void siginit(struct sigaction * def, sigset_t * mask, void (*handler)(int));
