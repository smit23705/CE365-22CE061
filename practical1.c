#include <stdio.h>
#include <string.h>

int isValidString(const char *input) {
    int i = 0;


    while (input[i] == 'a') {
        i++;
    }


    if (input[i] == 'b' && input[i + 1] == 'b' && input[i + 2] == '\0') {
        return 1; // Valid string
    }

    return 0; // Invalid string
}

int main() {
    char input[100];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove the newline character at the end of the input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Validate the string
        if (isValidString(input)) {
            printf("Valid String\n");
        } else {
            printf("Invalid String\n");
        }
    } else {
        printf("Error reading input\n");
    }

    return 0;
}
