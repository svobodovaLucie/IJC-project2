#include "htab.h"
#include "htab_structs.h"

// htab_for_each(t,funkce)

// projde všechny záznamy, na každý zavolá funkci
// (pozor na možné změny tabulky!)
// 
/**
 * @brief for_each: projde všechny záznamy a zavolá na ně funkci f
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @param f funkce, ktera se ma zavolat
 * @return void
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    for (unsigned i = 0; i < t->arr_size; i++) {
        if (t->arr[i] == NULL) {
            continue;
        }
        for (htab_item_t *item = t->arr[i]; item != NULL; item = item->next) {
            f(&(item->pair));
        }
    }
}


/*
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    for (unsigned i = 0; i < t->arr_size; i++) {
        if (t->arr[i] == NULL) {
            continue;
        }
        for (htab_item_t *item = t->arr[i]; item != NULL; item = item->next) {
            // zavolat funkci
            f(&(item->pair));
        }
    }
}
*/