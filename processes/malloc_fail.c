#include <stdio.h>
#include <stdlib.h>

int main() {
  size_t step = 1024 * 1024; // Start with 1MB steps
  size_t total_allocated = 0;
  void *ptr = NULL;

  while (1) {
    void *new_ptr = malloc(total_allocated + step);
    if (new_ptr == NULL) {
      break; // Stop if allocation fails
    }
    ptr = new_ptr; // Store the last successful allocation
    total_allocated += step;
  }

  printf("Maximum memory allocated: %zu MB\n", total_allocated / (1024 * 1024));

  // Free the allocated memory
  free(ptr);

  return 0;
}
