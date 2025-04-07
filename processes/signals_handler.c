#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_handler(int signum) {
    printf("Signal %d received. Now exiting pause().\n", signum);
}

int main() {
    signal(SIGINT, my_handler);

    printf("Process will pause and wait for any signal.\n");
    pause();  // Wait here until a signal arrives
    printf("We returned from pause().\n");

    return 0;
}