#include <stdio.h>
#include "htab.h"
#include "io.h"

#define MAX_CHAR 128

void print_info_about_word (htab_pair_t *data) {
    printf("%s\t%u\t\tindex: %lu\tstrlen: %lu\n", data->key, data->value, htab_hash_function(data->key)%5, strlen(data->key));
}

#include <stdlib.h>
#include <string.h>
#include "htab_structs.h"

int main(void) {
    htab_t *t = htab_init(5);
    char buffer[MAX_CHAR] = {0};
    
    while (read_word(buffer, MAX_CHAR, stdin) != EOF) {
        if (htab_lookup_add(t, buffer) == NULL) {
            goto error_malloc;
        }
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