#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

/**
 * @brief Funkce v tabulce t vyhledá záznam odpovídající řetězci key
 * 
 * @param t tabulka, ve které se má záznam vyhledat
 * @param key klíč, podle kterého je záznam vyhledán
 * @return pokud je záznam nalezen, vrací ukazatel na záznam, jinak vrací NULL
 */
htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }
    size_t index = htab_hash_function(key) % t->arr_size;
    size_t key_len = strlen(key);
    struct htab_item *item = t->arr[index];
    if (item != NULL) { // první položka pole na vypočteném indexu není prázdná
        size_t item_len = strlen(item->pair.key);
        for(; item != NULL; item = item->next){   // průchod seznamem a hledání daného klíče
            item_len = strlen(item->pair.key);
            if(item_len == key_len && !strncmp(key, item->pair.key, item_len)) {
                return &(item->pair);   // pokud je položka nalezena, je vrácen ukazatel na ni
            }
        }
    }
    // hledaný prvek nebyl nalezen - bude vytvořen nový
    struct htab_item *new = malloc(sizeof(struct htab_item));
    if(new == NULL){
        return NULL;
    }
    if ((new->pair.key = malloc(key_len + 1)) == NULL) {
        free(new);
        return NULL;
    }
    memcpy((char *)new->pair.key, key, key_len + 1);
    new->pair.value = 0;
    new->next = NULL;

    if (t->arr[index] == NULL) {
        t->arr[index] = new;
    } else {
        item->next = new;
    }
    
    t->size++;
    return &(new->pair);
}