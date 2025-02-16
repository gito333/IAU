#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int id = fork();
  if (id == 0) {
    printf("Hello From child");
  } else {
    printf("Hello from main process");
  }
}
