// htab_for_each.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Funkce projde všechny záznamy v tabulce a zavolá na ně funkci f.
 * 
 * @param t tabulka, na jejíž záznamy je funkce zavolána
 * @param f funkce, která se má zavolat
 * @return void
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    for (unsigned i = 0; i < t->arr_size; i++) {
        for (htab_item_t *item = t->arr[i]; item != NULL; item = item->next) {
            f(&(item->pair));
        }
    }
}