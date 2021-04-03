#include <string.h>
#include <stdlib.h>

#include "htab.h"
#include "htab_structs.h"

// b=htab_erase(t,key)
/**
 * @brief zrušení záznamu se zadaným klíčem (úspěch:true)
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param key klic, podle ktereho se zaznam vyhleda
 * @return true pokud zaznam byl nalezen a odstranen, false pokud nebyl nalezen
 */

bool htab_erase(htab_t * t, htab_key_t key) {
    for (unsigned i = 0; i < t->arr_size; i++) {
        for (htab_item_t *item = t->arr[i]; item != NULL; item = item->next) {
            if (!strcmp(item->pair.key, key)) {
                htab_item_t *tmp = item;
                item = item->next;
                free(item);
                return true;              
            }
        }
    }
    return false;
}