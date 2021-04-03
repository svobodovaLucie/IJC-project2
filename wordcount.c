#include <stdio.h>
#include "htab.h"
#include "io.h"

#define MAX_CHAR 128

void print_info_about_word (htab_pair_t *data) {
    printf("%s %u\n", data->key, data->value);
}

int main(int argc, char *argv[]) {
    FILE *f;
    if (argc == 1) {
        f = stdin;
    } else if (argc == 2) {
        f = fopen(argv[1], "r");
        if(f == NULL) {
            fprintf(stderr, "Error in opening file");
            return -1;
        }
    } else {
        fprintf(stderr, "Error: Invalid arguments");
        return -1;
    }

    htab_t *t = htab_init(5);
    size_t num = htab_size(t);
    size_t arr_num = htab_bucket_count(t);

    printf("The hash tab has %ld records and array size of %ld\n", num, arr_num);
    char buffer[MAX_CHAR] = {0};
    
    while (read_word(buffer, MAX_CHAR, f) != EOF) {
        htab_lookup_add(t, buffer);
        htab_find(t, buffer);
        memset(buffer, '\0', MAX_CHAR);
    }
   
    htab_for_each(t,print_info_about_word);

    num = htab_size(t);
    arr_num = htab_bucket_count(t);
    printf("The hash tab has %ld records and array size of %ld\n", num, arr_num);

    htab_free(t);
    fclose(f);
    return 0;
}