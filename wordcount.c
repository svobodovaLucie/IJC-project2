#include <stdio.h>
#include "htab.h"
#include "io.h"

// Ideální velikost hashovací tabulky by měla být prvočíslo - sníží se tak počet možných kolizí
// 
#define HTAB_SIZE 20763
#define MAX_CHAR 128

void print_info_about_word (htab_pair_t *data) {
    printf("%s\t%u\n", data->key, data->value);
}

int main(void) {
    htab_t *t = htab_init(HTAB_SIZE);
    if (t == NULL) {
        fprintf(stderr, "Error: htab_init: Not enough space for memory allocation.\n");
        return 1;
    }
    char buffer[MAX_CHAR] = {0};
    
    while (read_word(buffer, MAX_CHAR, stdin) != EOF) {
        htab_pair_t *pair = htab_lookup_add(t, buffer);
        if (pair == NULL) {
            goto error_malloc;
        }
        pair->value++;
        memset(buffer, '\0', MAX_CHAR);
    }
    htab_for_each(t,print_info_about_word);

    htab_free(t);
    return 0;

    error_malloc:
        fprintf(stderr, "Error: htab_lookup_add: Not enough space for memory allocation.\n");
        htab_free(t);
        return 1;
}