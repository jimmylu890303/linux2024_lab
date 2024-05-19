#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("Received SIGUSR1\n");
    sleep(10);
    printf("Finished handling SIGUSR1\n");
}

int main() {
    signal(SIGUSR1, handle_sigusr1);
    printf("Process ID: %d\n", getpid());
    while (1) {
        pause(); 
    }
    return 0;
}

