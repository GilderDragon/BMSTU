#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(char **s, int n) {
    // Calculate total length of resulting string
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += strlen(s[i]);
    }

    // Allocate memory for resulting string + null terminator
    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL; // Memory allocation error
    }

    // Copy all strings to resulting string
    int current_pos = 0;
    for (int i = 0; i < n; i++) {
        strcpy(result + current_pos, s[i]);
        current_pos += strlen(s[i]);
    }

    return result;
}

int main() {
    int n;

    // Read number of strings
    printf("Enter number of strings: ");
    scanf("%d", &n);

    // Consume newline character after number
    getchar();

    // Allocate memory for array of string pointers
    char **strings = (char **)malloc(n * sizeof(char *));
    if (strings == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    // Read strings
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        char buffer[1000]; // Buffer for reading string
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Allocate memory for string and copy content
        strings[i] = (char *)malloc(strlen(buffer) + 1);
        if (strings[i] == NULL) {
            printf("Memory allocation error\n");
            return 1;
        }
        strcpy(strings[i], buffer);
    }

    // Call concat function
    char *result = concat(strings, n);
    if (result == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    // Print result
    printf("Concatenation result: %s\n", result);

    // Free memory
    free(result);
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}