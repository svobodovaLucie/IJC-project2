// htab_lookup_add.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

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
    size_t index = htab_hash_function(key) % t->arr_size;
    size_t key_len = strlen(key);
    struct htab_item *item = t->arr[index];
    if (item != NULL) {     // seznam začínající na daném indexu není prázdný
        // prohledání seznamu, zda hledaný prvek již neexistuje
        for(; item->next != NULL; item = item->next){
            if(strlen(item->pair.key) == key_len && !strcmp(key, item->pair.key)) {
                return &(item->pair);
            }
        }
        if(strlen(item->pair.key) == key_len && !strcmp(key, item->pair.key)) {
            return &(item->pair);
        }
    }
    // vytvoření nového prvku
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

    // přiřazení prvku na správné místo
    if (t->arr[index] == NULL) {
        t->arr[index] = new;
    } else {
        item->next = new;
    }
    t->size++;
    return &(new->pair);
}