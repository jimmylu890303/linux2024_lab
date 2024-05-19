#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_rt_signal(int sig, siginfo_t *si, void *context) {
    printf("Received real-time signal %d with value %d\n", sig, si->si_value.sival_int);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_rt_signal;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);

    printf("Process ID: %d\n", getpid());
    while (1) {
        pause();
    }
    return 0;
}

