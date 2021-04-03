#include "htab.h"
#include "htab_structs.h"

#include <stdio.h>

// ptr=htab_find(t,key)
// vyhledávání - viz dále
/*
htab_pair_t *htab_find(htab_t *t, htab_key_t key);
V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
- pokud jej nalezne, vrátí ukazatel na záznam
- pokud nenalezne, vrátí NULL
*/
/**
 * @brief v tabulce  t  vyhledá záznam odpovídající řetězci  key
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param key klic, podle ktereho se zaznam vyhleda
 * @return pokud je zaznam nalezen, vrátí ukazatel na záznam, jinak vrátí NULL
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    unsigned index = (htab_hash_function(key) % t->arr_size);
    for (struct htab_item *i = t->arr[index]; i != NULL; i = i->next) {
        if (!strcmp(i->pair.key, key)) {
            printf("Nalezeno slovo %s na indexu %u\n", key, index);
            return &(i->pair);
        }
    }
    printf("Slovo %s nebylo nalezeno (index %u)\n", key, index);
    return NULL;
}