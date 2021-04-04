#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_structs.h"

/**
 * @brief zrušení záznamu se zadaným klíčem
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param key klic, podle ktereho se zaznam vyhleda
 * @return true pokud zaznam byl nalezen a odstranen, false pokud nebyl nalezen
 */
bool htab_erase(htab_t * t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    size_t key_len = strlen(key);
    htab_item_t *item = t->arr[index];
    htab_item_t *prev = NULL;
    for (; item != NULL; item = item->next) {
        size_t item_len = strlen(item->pair.key);
        if (item_len > key_len) {
            break;
        }
        if (key_len == item_len && !strcmp(item->pair.key, key)) {
            htab_item_t *tmp;
            if (prev == NULL) {
                tmp = t->arr[index];
                t->arr[index] = t->arr[index]->next;
            } else {
                tmp = item;
                prev->next = item->next;
            }
            free(tmp->pair.key);
            free(tmp);
            t->size--;
            return true;
        }
        prev = item;
    }
    return false;
}