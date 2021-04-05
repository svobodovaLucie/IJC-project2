#include <stdio.h>
#include "htab.h"
#include "htab_structs.h"

/**
 * @brief v tabulce  t  vyhledá záznam odpovídající řetězci  key
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param key klic, podle ktereho se zaznam vyhleda
 * @return pokud je zaznam nalezen, vrátí ukazatel na záznam, jinak vrátí NULL
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    unsigned index = (htab_hash_function(key) % t->arr_size);
    unsigned key_len = strlen(key);
    for (struct htab_item *item = t->arr[index]; item != NULL; item = item->next) {
        unsigned item_len = strlen(item->pair.key);
        if (item_len > key_len) {
            break; // nenalezeno
        }
        if ((key_len == item_len) && (!strcmp(item->pair.key, key))) {
            return &(item->pair);
        }
    }
    return NULL;
}