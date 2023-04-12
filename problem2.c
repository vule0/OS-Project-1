#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    char* cmd[argc];
    int count = 0, i;

    // getting command line arguments into array, skipping executable and "|"
    for (i = 0; i < argc; i++){
        if (i == 1 || i == 3){
            cmd[count] = argv[i];
            count++;
        }
    }
    //creating pipe
    int p[2];
    if (pipe(p) < 0){
        printf("Pipe failed!\n");
        exit(1);
    }

    //first process executes first command and writes output to pipe
    int process1 = fork();
    if (process1== 0){
        dup2(p[1], 1);
        close(p[1]);
        close(p[0]);
        execlp(cmd[0], cmd[0], NULL);
    }
    //second process reads from pipe and executes second command with input = first command's output
    int process2 = fork();
    if (process2  == 0){
        dup2(p[0], 0);
        close(p[1]);
        close(p[0]);
        execlp(cmd[1], cmd[1], NULL);
    }

    //closes pipe and waits for processes to finish
    close(p[1]);
    close(p[0]);
    waitpid(process1, NULL, 0);
    waitpid(process2, NULL, 0);
    printf("++++\n");
    return 1;
}