#include <stdio.h>
#include <stdlib.h>

#include "htab.h"
#include "htab_structs.h"

/**
 * @brief v tabulce  t  vyhledá záznam odpovídající řetězci  key
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param key klic, podle ktereho se zaznam vyhleda
 * @return pokud je zaznam nalezen, vrátí ukazatel na záznam, jinak vrátí NULL
 */

htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    size_t key_len = strlen(key);
    bool greater = false;
    struct htab_item * item = t->arr[index];
    if (item != NULL) {
        size_t item_len = strlen(item->pair.key);
        if (item_len > key_len) {
            greater = true;
        }
        for(; item->next != NULL; item = item->next){
            item_len = strlen(item->pair.key);
            if(item_len == key_len && strncmp(key, item->pair.key, item_len) == 0) {
                item->pair.value++; 
                return &(item->pair);
            }
            if (strlen(item->next->pair.key) > key_len) {
                greater = true;
                break;
            }
        }
        if (!greater) {
            item_len = strlen(item->pair.key);
            if(item_len == key_len && strncmp(key, item->pair.key, item_len) == 0) {
                item->pair.value++;
                return &(item->pair);
            }
        }
    }
    struct htab_item *new = malloc(sizeof(struct htab_item));
    if(new == NULL){
        return NULL;
    }
    if ((new->pair.key = malloc(key_len + 1)) == NULL) {
        free(new);
        return NULL;
    }
    memcpy(new->pair.key, key, key_len + 1);
    new->pair.value = 1;

    if (greater) {
        new->next = item->next;
    } else {
        new->next = NULL;
    }

    if (t->arr[index] == NULL) {
        t->arr[index] = new;
    } else if (greater && item == t->arr[index]) {
        new->next = item;
        t->arr[index] = new;
    } else {
        item->next = new;
    }
    
    t->size++;
    return &(new->pair);
}