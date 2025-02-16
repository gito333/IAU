#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int id = fork();
  int n = 0;

  if (id == 0) {
    n = 2;
  } else {
    n = 10;
  }
  if (id != 0) {
    wait(0);
  }
  for (int i = n; i < n + 19; i++) {
    printf("%d ", i);
    fflush(stdout);
    usleep(1000);
  }
  printf("\n");
  return 0;
}
