// htab_find.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Funkce v tabulce t vyhledá záznam odpovídající řetězci key.
 * 
 * @param t tabulka, ve které má být záznam vyhledán
 * @param key klíč, podle kterého je záznam vyhledán
 * @return pokud je záznam nalezen, vrácí ukazatel na záznam, jinak vrací NULL
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    unsigned index = (htab_hash_function(key) % t->arr_size);
    unsigned key_len = strlen(key);
    for (struct htab_item *item = t->arr[index]; item != NULL; item = item->next) {
        if ((key_len == strlen(item->pair.key)) && (!strcmp(item->pair.key, key))) {
            return &(item->pair);
        }
    }
    return NULL;
}