#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = NULL;
    int initial_size = 5;
    int new_size = 10;

    // 1. Initial allocation using malloc
    arr = (int *)malloc(initial_size * sizeof(int));
    
    // Deliberate flaw (a): Unchecked allocation return value (simulated or potential failure)
    // If malloc fails, arr is NULL, but we proceed without checking.
    printf("Initial allocation at address: %p, size: %d elements\n", (void *)arr, initial_size);

    for (int i = 0; i < initial_size; i++) {
        arr[i] = i + 1;
    }

    // 2. Reallocation using realloc
    arr = (int *)realloc(arr, new_size * sizeof(int));
    printf("Reallocated array at address: %p, new size: %d elements\n", (void *)arr, new_size);

    for (int i = initial_size; i < new_size; i++) {
        arr[i] = (i + 1) * 10;
    }

    // Print values
    for (int i = 0; i < new_size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // 3. Freeing the memory
    free(arr);

    // Deliberate flaw (b): Use-after-free through a dangling pointer
    // arr is not set to NULL after free, and we attempt to write to it.
    printf("\n[WARNING] Accessing dangling pointer after free:\n");
    arr[0] = 999; // Use-after-free / dangling pointer dereference
    printf("Value at arr[0] after free: %d\n", arr[0]);

    return 0;
}
