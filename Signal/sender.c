#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid> <signal value> or <pid>\n", argv[0]);
        exit(1);
    }

    pid_t pid = atoi(argv[1]);
    if(argc == 3){
    	int value = atoi(argv[2]);
    	union sigval sv;
    	sv.sival_int = value;
    	sigqueue(pid, SIGUSR1, sv);
    }
    else{
    	kill(pid, SIGUSR1);
    }
    return 0;
}

