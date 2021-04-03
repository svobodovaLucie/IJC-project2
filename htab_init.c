#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

// t=htab_init(numb)
// Když htab_init nebo htab_lookup_add nemohou alokovat paměť,
// vrací NULL (a uživatel musí testovat výsledek těchto operací)
/**
 * @brief konstruktor: vytvoření a inicializace tabulky
 * 
 * @param n počet prvků pole (.arr_size)
 * @return ukazatel na alokovanou tabulku nebo NULL v pripade neuspesne alokace pameti
 */

htab_t *htab_init(size_t n) {
    htab_t *tab = malloc(sizeof(htab_t) + n * sizeof (htab_pair_t*));
    if (tab == NULL) {
        fprintf(stderr, "Error: htab_init: Not enough space for memory allocation.");
        return NULL;
    }
    tab->arr_size = n;
    tab->size = 0;
    for (size_t i = 0; i < n; i++) {
        tab->arr[i] = NULL;
    }
    return tab;
}