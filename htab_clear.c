// htab_clear.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Funkce zruší všechny položky tabulky t (tabulka zůstane prázdná).
 * 
 * @param t hashovací tabulka, jejíž záznamy mají být smazány
 * @return void
 */
void htab_clear(htab_t * t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item= t->arr[i];
        while (item != NULL) {
            htab_item_t *tmp = item;
            item = item->next;
            free((char *)tmp->pair.key);
            free(tmp);
        }
        t->arr[i] = NULL;
    }
    t->size = 0;
}
