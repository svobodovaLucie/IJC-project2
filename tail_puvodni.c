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
    //printf("Signed num je: %ld\n", num_convert);
    if (num_convert < 0) {
        fprintf(stderr, "Invalid number %ld (must be positive number).\n", num_convert);
        return -1;
    }

    if (num_str[0] == '+') {

        num_convert = -(num_convert);
    }
    //printf("Final unsigned num je: %ld\n", num_convert);
    //printf("Abs num je: %ld\n", ABS(num_convert));
    
    *num = num_convert;
    return 0;
}

/*int argument_parser(int argc, char *argv[]) {

    switch (argc)
    {
    case 0:
        return 1;       // have to read from stdin
        //break;
    case 1:
        //file = argv[1]; // signalize to read argv[1]
        // file
        break;
    case 2:
    case 3:
    // TODO DAT ARGUMENT &NUM K ULOZENI CISLA DO POLE
        if (!strcmp(argv[1], "-n") && !number_check(argv[2], &num)) {
            //v poradku, ulozit
        }
        else {
            // error
        }
        break;
        if (argc == 3) {
            // file = argv[3]
        } else {
            return 1; // read from stdin
        }
    case 3:
        break;
    default:
        fprintf(stderr, "Error: invalid arguments.\n");
        //return -1;
        break;
    }

    number_check(argv[1]);
    printf("%s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);
    return 0;
}
*/

// rozdelit na tail s + a tail bez
int tail_plus(FILE *file, int num) {
    unsigned i = 0;
    unsigned number = ABS(num);
    char buffer[MAX_CHARS];
    while (fgets(buffer, MAX_CHARS, file) != NULL) {
        printf("Buffer max-1: %c, max-2: %c, max-3: %c        ", buffer[MAX_CHARS-1], buffer[MAX_CHARS-2], buffer[MAX_CHARS-3]);
        if (buffer[strlen(buffer)-1] != '\n') {
            fprintf(stderr, "Max length of a line is 510 characters. Next characters will be ignored.\n");
            buffer[strlen(buffer)-1] = '\n';
            //buffer[MAX_CHARS-1] = '\0';
        }
        if (i >= number - 1) {
            printf("%*s", MAX_CHARS, buffer);
        }
        memset(buffer, '\0', MAX_CHARS-1);
        i++;
    }
    return 0;
}

/*
// nebude ten postup stejny ani podobny, tak je blbost ho mit v jedne fci
int tail(FILE *file, int num) {

    printf("HELLO GUYS\n");
    //char *buffer = (char*)calloc(ABS(num));
    return 0;
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
    if (tail_plus(file, num)) {
        return -1;
    }

    return 0;
}

