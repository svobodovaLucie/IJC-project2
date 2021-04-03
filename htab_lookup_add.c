#include "htab.h"
#include "htab_structs.h"

#include <stdio.h>
#include <stdlib.h>

// ptr=htab_lookup_add(t,key)

// vyhledávání+přidání - viz dále
// Když htab_init nebo htab_lookup_add nemohou alokovat paměť,
// vrací NULL (a uživatel musí testovat výsledek těchto operací)
/*
Funkce
htab_pair_t htab_lookup_add(htab_t *t, htab_key_t key);
V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
- pokud jej nalezne, vrátí ukazatel na záznam
- pokud nenalezne, automaticky přidá záznam a vrátí ukazatel
Poznámka: Dobře promyslete chování této funkce k parametru key.
Poznámka: podobně se chová C++ operator[] pro std::unordered_map
*/

/**
 * @brief v tabulce  t  vyhledá záznam odpovídající řetězci  key
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param key klic, podle ktereho se zaznam vyhleda
 * @return pokud je zaznam nalezen, vrátí ukazatel na záznam, jinak vrátí NULL
 */
htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    htab_item_t *item;
    htab_item_t *prev = NULL;
    for (item = t->arr[index]; item != NULL; item = item->next) {
        if (!strcmp(item->pair.key, key)) {
            item->pair.value++;
            return &(item->pair);
        }
        prev = item;
    }
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL) {
        fprintf(stderr, "Error: htab_lookup_add: Not enough space for memory allocation.\n");
        return NULL;
    }
    new->next = NULL;
    
    // TODO - this block is quite suspicious
    new->pair.key = malloc(strlen(key)+1);
    if (new->pair.key == NULL) {
       free(new);
       fprintf(stderr, "Error: lookup: Chyba alokace pameti.\n");
       return NULL;
    } 
    memcpy(new->pair.key, key, strlen(key)+1);  // TODO - memcpy warnings - pointer types
    
    new->pair.value = 1;
    if (prev == NULL) {
        t->arr[index] = new;
    } else {
        prev->next = new;
    }
    t->size++;
    return &(new->pair);
}


/*
htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    htab_item_t *item;
    htab_item_t *prev = NULL;
    for (item = t->arr[index]; item != NULL; item = item->next) {
        if (!strcmp(item->pair.key, key)) {
            item->pair.value++;
            return &(item->pair);
        }
        prev = item;
    }
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL) {
        fprintf(stderr, "Error: htab_lookup_add: Not enough space for memory allocation.\n");
        return NULL;
    }
    new->next = NULL;
    new->pair.key = key;
    new->pair.value = 1;
    if (prev == NULL) {
        t->arr[index] = new;
    } else {
        prev->next = new;
    }
    t->size++;
    return &(new->pair);
}
*/

/*
htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    htab_item_t *item;
    for (item = t->arr[index]; item != NULL; item = item->next) {
        if (!strcmp(item->pair.key, key)) {
            item->pair.value++;
            return &(item->pair);
        }
    }
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL) {
        fprintf(stderr, "Error: htab_lookup_add: Not enough space for memory allocation.\n");
        return NULL;
    }
    new->next = NULL;
    new->pair.key = key;
    new->pair.value = 1;
    t->arr[index] = new;
    t->size++;
    return &(new->pair);
}
*/
/*
htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    for (htab_item_t *item = t->arr[index]; item != NULL; item = item->next) {
        if (!strcmp(item->pair.key, key)) {
            item->pair.value++;
            return &(item->pair);
        }
    }
    htab_item_t *new = malloc(sizeof(htab_item_t));
    new->next = NULL;
    new->pair.key = key;
    new->pair.value = 1;
    return &(new->pair);
}

*/

/*
htab_pair_t * htab_lookup_add(htab_t *t, htab_key_t key) {
    unsigned index = (htab_hash_function(key) % t->arr_size);
    struct htab_item *i = t->arr[index];
    for (; i != NULL; i = i->next) {
        if (!strcmp(i->pair.key, key)) {
            // nasli jsme ji
            printf("Zaznam uz tam je");
            return &(i->pair);  // WTFFFFFFFFFF &
        }
        if (i->next == NULL) {
            // nenasli jsme, musime pridat -> jsme na konci toho seznamu, takze muzeme pridat na konec
            break;  
        }
    }
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL) {
        fprintf(stderr, "Error: htab_lookup_add: Not enough space for memory allocation");
        return NULL;
    }
    new->pair.key = key;
    new->pair.value = 1;
    new->next = NULL;
    i->next = new;
    printf("Pridali jsme novy zaznam.");
    return &(new->pair);
}
*/