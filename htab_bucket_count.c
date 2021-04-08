// htab_bucket_count.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Funkce vrací počet prvků pole tabulky t.
 * 
 * @param t tabulka, jejíž velikost má být zjištěna
 * @return počet prvků pole (.arr_size)
 */
size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}
