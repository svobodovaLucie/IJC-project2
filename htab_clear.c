#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

/**
 * @brief zrušení všech položek, tabulka zůstane prázdná
 * 
 * @param t hashovaci tabulka, jejiz zaznamy se maji smazat
 * @return void
 */
void htab_clear(htab_t * t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item= t->arr[i];
        while (item != NULL) {
            htab_item_t *tmp = item;
            item = item->next;
            free(tmp->pair.key);
            free(tmp);
        }
        t->arr[i] = NULL;
    }
    t->size = 0;
}