#define N 10 // Define a constant N with the value 10

// Global variables:
int i;                      // An integer loop counter/process identifier
int pipe_datos[2];          // File descriptors for a pipe intended for data
int pipe_pid[2];            // File descriptors for a pipe intended for PIDs
pid_t pid[N];               // Array to store Process IDs of N children
pid_t pid_aux;              // Auxiliary variable to store a PID

// Signal handler function f1 (likely for SIGUSR1)
void f1(int s) { // s is the signal number, unused here
    // If the 'i' value associated with this process is less than N-1
    if (i < N - 1)
        // Read a PID from pipe_pid's read end into the global pid_aux
        read(pipe_pid[0], &pid_aux, sizeof(pid_t));

    // Get the current process's own PID
    pid_t pid2 = getpid();
    // Write the current process's PID to pipe_pid's write end
    write(pipe_pid[1], &pid2, sizeof(pid_t));

    // If this process is the one associated with i = 0 (the first child created)
    if (i == 0)
        f2(0); // Call function f2 directly
    else
        // Otherwise, send SIGUSR1 signal to the process whose PID is pid[i-1]
        // (This is the PID of the previously created sibling, stored by the parent)
        kill(pid[i - 1], SIGUSR1);
}

// Signal handler function f2 (likely for SIGUSR2)
void f2(int s) { // s is the signal number, unused here
    // Create a character: ASCII '0' plus the 'i' value associated with this process
    char c1 = '0' + i;
    // Write this character to pipe_datos' write end
    write(pipe_datos[1], &c1, 1);

    // If the 'i' value associated with this process is less than N-1
    if (i < N - 1)
        // Send SIGUSR2 signal to the process whose PID is stored in the global pid_aux
        // (This PID was read from pipe_pid by this process in f1)
        kill(pid_aux, SIGUSR2);

    // Terminate the current process
    exit(0);
}

// Main function
int main(void) {
    struct sigaction a1; // Structure for signal handling configuration
    sigemptyset(&a1.sa_mask); // Initialize the signal mask (block no signals during handler)
    a1.sa_flags = 0; // No special flags

    // Configure and register signal handler f1 for SIGUSR1
    a1.sa_handler = f1;
    sigaction(SIGUSR1, &a1, NULL); /* Statement A */

    // Configure and register signal handler f2 for SIGUSR2
    a1.sa_handler = f2;
    sigaction(SIGUSR2, &a1, NULL); /* Statement B */

    // Create the two pipes
    pipe(pipe_datos);
    pipe(pipe_pid);

    // Loop N times to create N child processes
    for (i = 0; i < N; i++) {
        // Fork and store child PID in parent's pid array. Check if current process is the child.
        if ((pid[i] = fork()) == 0) { // Child process code
            // If this is the last child created (i == N-1)
            if (i == N - 1)
                f1(0); /* Statement D: Immediately invoke f1 */
            // All children enter an infinite loop, waiting for signals
            while (1) {}
        }
        // Parent continues the loop to create the next child
    }

    // Parent process code after creating all children
    for (i = 0; i < N; i++) {
        char c2; // Character buffer
        // Wait for the specific child pid[i] to terminate
        waitpid(pid[i], NULL, 0);
        // Read one character from pipe_datos' read end
        read(pipe_datos[0], &c2, 1); /* Statement C */
        // (The character c2 is read but not used in this snippet)
    }
    return 0; // Parent exits
} /* END PROGRAM */
