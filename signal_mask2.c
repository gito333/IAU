#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t sigterm_received = 0;

void sigterm_handler(int signum) {
    sigterm_received = 1;
    write(STDOUT_FILENO, "SIGTERM received after alarm.\n", 30);
}

void sigalrm_handler(int signum) {
    write(STDOUT_FILENO, "Alarm triggered: Unmasking SIGTERM.\n", 36);

    sigset_t unblock;
    sigemptyset(&unblock);
    sigaddset(&unblock, SIGTERM);
    sigprocmask(SIG_UNBLOCK, &unblock, NULL);

    struct sigaction sa;
    sa.sa_handler = sigterm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);
}

void sigusr1_handler(int signum) {
    pid_t pid = fork();
    if (pid == 0) {
        write(STDOUT_FILENO, "Child process created. Masking SIGALRM.\n", 41);

        sigset_t block;
        sigemptyset(&block);
        sigaddset(&block, SIGALRM);
        sigprocmask(SIG_BLOCK, &block, NULL);

        pause(); 
        _exit(0);
    } else if (pid > 0) {
        write(STDOUT_FILENO, "Parent handled SIGUSR1.\n", 24);
    } else {
        perror("fork");
    }
}

int main() {
    struct sigaction sa_usr;
    sa_usr.sa_handler = sigusr1_handler;
    sigemptyset(&sa_usr.sa_mask);
    sa_usr.sa_flags = 0;
    sigaction(SIGUSR1, &sa_usr, NULL);

    struct sigaction sa_alrm;
    sa_alrm.sa_handler = sigalrm_handler;
    sigemptyset(&sa_alrm.sa_mask);
    sa_alrm.sa_flags = 0;
    sigaction(SIGALRM, &sa_alrm, NULL);

    sigset_t block;
    sigemptyset(&block);
    sigaddset(&block, SIGTERM);
    sigprocmask(SIG_BLOCK, &block, NULL);

    alarm(10);
    write(STDOUT_FILENO, "SIGTERM blocked. Alarm set for 10s.\n", 36);

    while (1) {
        pause(); // wait for signal
    }

    return 0;
}
