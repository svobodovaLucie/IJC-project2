// tail.c
// Řešení IJC-DU2, příklad a), 28.03.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHARS 512   // maximální délka řádku (včetně koncové '\0')
#define DEF_LINES 10    // defaultní počet řádků k výpisu (bez zadání paramentů)

#define ABS(n) ((n < 0) ? (-n) : (n))

/**
 * @brief Funkce zkontroluje, zda je zadané číslo validní.
 * 
 * @param num_str číslo ve formátu řetězce
 * @param num ukazatel na výsledek 
 *            - výsledek je kladný, pokud argument je ve tvar k
 *            - výsledek je záporný, je-li argument ve tvaru +k
 * @return -1 pokud číslo (ve formátu řetězce) není validní, 
 *          1 pokud číslo je rovno 0
 *          0 pokud je číslo v pořádku
 */
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
        return 1;   // 0 řádků k vytisknutí
    }
    *num = num_convert;
    return 0;
}

/**
 * @brief Funkce uvolní paměť alokovanou pro prvních "to_free" prvků.
 * 
 * @param buffer 2D pole s uloženými řádky
 * @param to_free počet prvků k uvolnění
 * @return void
 */
void buffer_free(char **buffer, unsigned to_free) {
    for (unsigned i = 0; i < to_free; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

/**
 * @brief Funkce vytiskne řádky začínající řádkem číslo "num".
 * 
 * @param file soubor, ze kterého jsou řádky čtené
 * @param num číslo řádku, od kterého se má tisknout
 * @return void
 */
void tail_plus(FILE *file, long int num) {
    char buffer[MAX_CHARS] = {0};
    unsigned line = 0;
    bool longer_line = false;
    while (fgets(buffer, MAX_CHARS - 1, file) != NULL) {
        if (buffer[strlen(buffer) - 1] != '\n') {
            if (!longer_line) {
                fprintf(stderr, "Max length of a line is %d characters.\n", MAX_CHARS - 1);
                longer_line = true;
            }
            int c;
            while ((c = fgetc(file)) != '\n') {
               ; // prázdný cyklus
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

/**
 * @brief Funkce vytiskne posledních "num" řádků.
 * 
 * @param file soubor, ze kterého jsou řádky čtené
 * @param num počet řádků k vytisknutí
 * @return  0 pokud byl tisk úspěšný
 *         -1 pokud je nedostatek místa k alokaci (+ nic není vytištěno)
 */
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
    bool longer_line = false;
    while (fgets(buffer[num_of_line % num], MAX_CHARS-1, file) != NULL) {
        if (buffer[num_of_line % num][strlen(buffer[num_of_line % num]) - 1] != '\n') {            
            if (!longer_line) {
                fprintf(stderr, "Max length of a line is %d characters.\n", MAX_CHARS - 1);
                longer_line = true;
            }
            int c;
            while ((c = fgetc(file)) != '\n') {
                ;    // prázdný cyklus
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

    // zpracování argumentů příkazové řádky
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
            if (num_check_res == -1) {  // nevalidní argumenty
                return 1;
            }
            if (num_check_res == 1) {   // 0 řádků k tisku - program může skončit
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

    // funkce tail
    if (num <= 0) { // vytiskne řádky začínající řádkem číslo "num"
        tail_plus(file, ABS(num));
    } 
    else {          // vytiskne posledních "num" řádků
        if (tail(file, num)) {
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return 0;
}