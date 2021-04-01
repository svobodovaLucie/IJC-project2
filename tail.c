// tail.c
// Řešení IJC-DU2, příklad a), 28.03.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 511
#define DEF_LINES 10

#define ABS(n) ((n < 0) ? (-n) : (n))

// Function checks if string is a positive number
// Returns -1 if the number is invalid
// Returns 1 if the arguments are -n 0 (zero lines to be printed)
// else returns 0 and the valid num is in variable num
// var num is positive if the argument is k
// var num is negative if the argument is +k
int number_check(char *num_str, long *num) {
    char *ptr;
    long int num_convert = strtol(num_str, &ptr, 10);
    if (*ptr != '\0') {
        fprintf(stderr, "Invalid argument ( -n %s).\n", num_str);
        return -1;
    }
    if (num_convert < 0 || (num_convert == 0 && num_str[0] == '-')) {
        fprintf(stderr, "Invalid number %ld (must be positive number).\n", num_convert);
        return -1;
    }

    if (num_str[0] == '+') {
        num_convert = -(num_convert);
    }

    if (num_convert == 0 && num_str[0] != '+') {
        return 1;   // 0 lines to be printed
    }
    *num = num_convert;
    return 0;
}

// Function frees the first "to_free" elements in buffer
void buffer_free(char **buffer, unsigned to_free) {
    for (unsigned i = 0; i < to_free; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

// Function prints lines starting from line number "num"
void tail_plus(FILE *file, long int num) {
    char buffer[MAX_CHARS] = {0};
    unsigned line = 0;

    while (fgets(buffer, MAX_CHARS - 1, file) != NULL) {
        if (buffer[strlen(buffer) - 1] != '\n') {
            fprintf(stderr, "Max length of a line is %d characters (line %u is longer).\n", MAX_CHARS - 1, line);
            int c;
            while ((c = fgetc(file)) != '\n') {
               ; // empty loop
            }
            buffer[strlen(buffer)] = '\n';
        }
        if (line >= num - 1) {
            printf("%s", buffer);
        }
        memset(buffer, '\0', MAX_CHARS);
        line++;
    }
}

// Function prints the last "num" of lines
// returns 0 when successful
// returns -1 if not enough space for memory allocation - nothing is printed
int tail(FILE *file, long int num) {
    char **buffer = (char**)calloc(num, sizeof(char*));
    if (buffer == NULL) {
        fprintf(file, "Error: Not enough space for memory allocation.\n");
        return -1;
    }
    for (unsigned i = 0; i < num; i++) {
        buffer[i] = (char*)calloc(MAX_CHARS, 1);
        if (buffer[i] == NULL) {
            fprintf(file, "Error: Not enough space for memory allocation (row number %ul)\n", i);
            buffer_free(buffer, i);
            return -1;
        }
    }
    unsigned num_of_line = 0;
    while (fgets(buffer[num_of_line % num], MAX_CHARS-1, file) != NULL) {
        if (buffer[num_of_line % num][strlen(buffer[num_of_line % num]) - 1] != '\n') {
            fprintf(stderr, "Max length of a line is %d characters (line %u is longer).\n", MAX_CHARS - 1, num_of_line);
            int c;
            while ((c = fgetc(file)) != '\n') {
                ;    // prazdny cyklus
            }
            buffer[num_of_line % num][strlen(buffer[num_of_line % num])] = '\n';
        }
        num_of_line++;
    }
    unsigned j = num_of_line % num;
    do {
        printf("%s", buffer[j % num]);
        j++;
    } while ((j % num) != (num_of_line % num));

    buffer_free(buffer, num);
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *file = stdin;
    long int num;

    // parse arguments
    switch (argc) {
    case 1:
        num = 10;
        break;
    case 2:
        if ((file = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "Error: The file doesn't exist.\n");
            return 1;
        }
        num = 10;
        break;
    case 3:
    case 4:
        if (!strcmp(argv[1], "-n")) {
            int num_check_res = number_check(argv[2], &num);
            if (num_check_res == -1) {  // invalid arguments
                return 1;
            }
            if (num_check_res == 1) {   // 0 lines to be printed
                return 0;
            }
        } else {
                fprintf(stderr, "Error: Invalid arguments.\n");
                return 1;
        }
        if (argc == 4) {
            if((file = fopen(argv[3], "r")) == NULL) {
                fprintf(stderr, "Error: The file doesn't exist.\n");
                return 1;
            }
        }
        break;
    default:
        fprintf(stderr, "Error: invalid arguments.\n");
        break;
    }

    // tail functions
    if (num <= 0) { // prints lines starting from line "num"
        tail_plus(file, ABS(num));
    } 
    else {          // prints last "num" lines
        if (tail(file, num)) {
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return 0;
}
