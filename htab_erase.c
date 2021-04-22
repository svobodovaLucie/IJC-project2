// htab_erase.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Funkce zruší záznam se zadaným klíčem.
 * 
 * @param t tabulka, ze které má být záznam zrušen
 * @param key klíč, podle kterého je záznam vyhledán
 * @return true pokud záznam byl nalezen a odstraněn, false pokud nalezen nebyl
 */
bool htab_erase(htab_t * t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    size_t key_len = strlen(key);
    htab_item_t *item = t->arr[index];
    htab_item_t *prev = NULL;   // prvek předcházející prvku, který má být vymazán
    for (; item != NULL; item = item->next) {
        if (key_len == strlen(item->pair.key) && !strcmp(item->pair.key, key)) {
            // odstranění nalezeného prvku
            htab_item_t *tmp;
            if (prev == NULL) {
                tmp = t->arr[index];
                t->arr[index] = t->arr[index]->next;
            } else {
                tmp = item;
                prev->next = item->next;
            }
            free((char *)tmp->pair.key);
            free(tmp);
            t->size--;
            return true;
        }
        prev = item;
    }
    return false;
}
