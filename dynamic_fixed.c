#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = NULL;
    int initial_size = 5;
    int new_size = 10;

    // 1. Initial allocation with null check
    arr = (int *)malloc(initial_size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    
    printf("Initial allocation successful at address: %p\n", (void *)arr);

    for (int i = 0; i < initial_size; i++) {
        arr[i] = i + 1;
    }

    // 2. Safe reallocation pattern (using a temporary pointer to prevent memory leaks if realloc fails)
    int *temp = (int *)realloc(arr, new_size * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory reallocation failed! Existing memory is preserved.\n");
        free(arr);
        arr = NULL;
        return 1;
    }
    arr = temp;
    printf("Reallocation successful at address: %p\n", (void *)arr);

    for (int i = initial_size; i < new_size; i++) {
        arr[i] = (i + 1) * 10;
    }

    // Print values
    for (int i = 0; i < new_size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // 3. Safe deallocation
    free(arr);
    arr = NULL; // Set pointer to NULL to prevent dangling pointer bugs

    if (arr == NULL) {
        printf("\nMemory freed successfully and pointer safely set to NULL.\n");
    }

    return 0;
}
