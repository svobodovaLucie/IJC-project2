// htab_init.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Konstruktor: Funkce vytvoří a inicializuje tabulku.
 * 
 * @param n počet prvků pole (.arr_size)
 * @return ukazatel na alokovanou tabulku nebo NULL v případě neúspěšné alokace paměti
 */
htab_t *htab_init(size_t n) {
    htab_t *tab = malloc(sizeof(htab_t) + n * sizeof (htab_pair_t*));
    if (tab == NULL) {
        return NULL;
    }
    tab->arr_size = n;
    tab->size = 0;
    for (size_t i = 0; i < n; i++) {
        tab->arr[i] = NULL;
    }
    return tab;
}