#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signum) {
    printf("Alarm went off! signum=%d\n", signum);
}

int main() {
    // Set handler for SIGALRM
    signal(SIGALRM, alarm_handler);

    // Schedule alarm in 5 seconds
    alarm(5);
    printf("Alarm set for 5 seconds.\n");

    // Wait indefinitely for signals
    while (1) {
        pause();
    }
    return 0;
}