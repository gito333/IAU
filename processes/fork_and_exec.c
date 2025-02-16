#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  // Attempt to fork the process
  pid_t pid = fork();

  if (pid == -1) {
    // Handle fork failure
    fprintf(stderr, "Error fork\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child process\n");

    // Create a grandchild process
    pid_t child_pid = fork();

    if (child_pid == -1) {
      fprintf(stderr, "Error fork\n");
      return 1;
    } else if (child_pid == 0) {
      // Grandchild process
      printf("hola\n");
    } else {
      // Still inside the original child process
      printf("adios\n");
    }
  } else {
    // Parent process
    printf("IAU\n");
  }

  return 0;
}
