#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    char* cmd = argv[1];
    char* parameters[argc];
    int i;
    // add parameters to array
    for (i = 1; i < argc + 1; i++){
        parameters[i-1] = argv[i];
    }
    // create fork, where child executes cmd with parameters, and parent waits for child to finish 
    int child = fork();
    if (child > 0){
        wait(NULL);
        printf("++++\n");
    }
    else{
        execvp(cmd, parameters);
    }
    return 1;
}