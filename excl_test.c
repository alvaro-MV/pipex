#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);  
    }
    if (pid == 0) {
        close(pipefd[0]); // Close read end
        sleep(2);
        write(pipefd[1], "done", 4);
        close(pipefd[1]); // Close write end
        exit(EXIT_SUCCESS);
    }
    close(pipefd[1]); // Close write end
    close(pipefd[0]); // Close read end
    sleep(2);
    wait(NULL);
    return 0;
}