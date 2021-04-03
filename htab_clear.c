#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "htab_structs.h"

// htab_clear(t)
/**
 * @brief zrušení všech položek, tabulka zůstane prázdná
 * 
 * @param t hashovaci tabulka, jejiz zaznamy se maji smazat
 * @return void
 */
void htab_clear(htab_t * t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr[i] == NULL) continue;
        htab_item_t *item= t->arr[i];
        while (item != NULL) {
            htab_item_t *tmp = item;
            free(item->pair.key);   // TODO - warning: want to free const*
            item = item->next;
            free(tmp);
        }
    }
    t->size = 0;
}


/*
void htab_clear(htab_t * t) {
    for (unsigned i = 0; i < t->arr_size; i++) {
        for (htab_item_t *item = t->arr[i]; item != NULL; item = item->next) {
            htab_item_t *tmp = item;
            item = item->next;
            free(tmp);
        }
        free(t->arr[i]);
    }
    t->size = 0;
}
*/
