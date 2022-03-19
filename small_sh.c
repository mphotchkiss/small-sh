#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
void remove_line(char *);

int DEBUG = 0; //for personal use - helps with printf debugging

int accept(char * input, int * status) {
    if (!strcmp(input, "exit")) //if we exit
        return 0;
    else {
        if (input[0]=='#' || input[0]=='\0') //if comment or blank line
            return 1;
        else if (!strcmp(input, "cd")) { //if the request is home
            chdir(getenv("HOME"));
            char * buf;
        }
        else if (input[0] == 'c' && input[1] == 'd' && input[2] == ' ') { //if our command is 'cd somestuff'
            if (DEBUG)
                printf("Input inside if: %s \n", input);
            char p [strlen(input)-3];
            if (DEBUG)
                printf("Path: %s \n", p);
            for (int i = 3; i < strlen(input); i++) {
                p[i-3] = input[i];
                if (DEBUG) {
                    printf("Copying input[%d] to path[%d]: %c \n", i, i-3, input[i]);
                    printf("Path: %s \n", p);
                }
            }
            p[strlen(input)-3] = '\0';
            if (DEBUG)
                printf("Path: %s \n", p);
            if(chdir(p) < 0) {
                printf("Invalid arguments for command cd\n");
            }
        }
        else if (!strcmp(input, "status")) { //if we want the status
            //handle status command
            printf("exit value %d \n", *status);
        }
        else { //a non-built-in command (aka not cd, status, nor exit)
            char * command;
            char * save;
            command = strtok_r(input, " ", &save);
            printf("Command: %s \n", command);
            char ** argv;
            while (command = strtok_r(NULL, " ", &save)){
                if (DEBUG)
                    printf("Command: %s \n", command);
            }
            //int execvp(char * path, char * argv[])
        }
        return 1; //user did not exit so maintain shell w/ a return of 1
    }
}

int main() {
    char * input = malloc(sizeof(char)*2049);
    printf(": ");
    fgets(input, sizeof(char)*2049, stdin);
    remove_line(input);
    int status = 0;
    while(accept(input, &status)) {
        free(input);
        input = malloc(sizeof(char)*2049);
        printf(": ");
        fgets(input, sizeof(char)*2049, stdin);
        remove_line(input);
    }
    return 0;
}

void remove_line(char * input) {
    input[strlen(input)-1] = '\0';
    if (DEBUG)
        printf("Input after removal: %s \n", input);
}
