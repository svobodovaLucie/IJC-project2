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
int number_check(char *num_str, long *num) {
    char *ptr;
    long int num_convert = strtol(num_str, &ptr, 10);
    if (*ptr != '\0') {
        fprintf(stderr, "Invalid argument ( -n %s).\n", num_str);
        return -1;
    }
    if (num_convert < 0) {
        fprintf(stderr, "Invalid number %ld (must be positive number).\n", num_convert);
        return -1;
    }

    if (num_str[0] == '+') {
        num_convert = -(num_convert);
    }
    *num = num_convert;
    return 0;
}

int tail_plus(FILE *file, long int num) {
    char buffer[MAX_CHARS] = {0};
    unsigned line = 0;

    while (fgets(buffer, MAX_CHARS - 1, file) != NULL) {
        if (buffer[strlen(buffer) - 1] != '\n') {
            fprintf(stderr, "Moc dlouhe radky.\n");
            do {
                fseek(file, 1, SEEK_CUR);
            }
            while (fgetc(file) != '\n');
            buffer[strlen(buffer)] = '\n';
        }
        if (line >= num - 1) {
            printf("%s", buffer);
        }
        memset(buffer, '\0', MAX_CHARS);
        line++;
    }
    return 0;
}

/*
int tail(FILE *file, long int num) {
    // naalokovat buffer pro n radku
    // dynamicka alokace - prvne row, pak cells

    // prochazet file, ukladat radek
    char *buffer = calloc(num - 1, 1);
    if (buffer == NULL) {
        fprintf(stderr, "Nedostatek pameti.\n");
        return -1;
    }
    for (unsigned i = 0; i < num; i++) {
        buffer[i] = calloc(MAX_CHARS - 1, 1);
        if (buffer[i] == NULL) {
            fprintf(stderr, "Nedostatek pameti.\n");
            // free alokovane
            for (; i >= 0; i--) {
                free(buffer[i]);
            }
            return -1;
        }
    }

    for (unsigned i = 0; i < num; i++) {
        free(buffer[i]);
    }

}
*/

int main(int argc, char *argv[]) {
    FILE *file = stdin;
    long int num;

    // parse arguments
    switch (argc)
    {
    case 1:
        break;
    case 2:
        if ((file = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "Error: The file doesn't exist.\n");
            return 1;
        }
        break;
    case 3:
    case 4:
        if (strcmp(argv[1], "-n") || number_check(argv[2], &num)) {
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

    /////////////////////////////
    if (num < 0) {
        if (tail_plus(file, ABS(num))) {
            return -1;
        }
    } 
    /*
    else {
        if (tail(file, num)) {
            return -1;
        }
    }
    */

    return 0;
}
