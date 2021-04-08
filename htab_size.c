// htab_size.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Funkce vrací počet prvků tabulky.Konstruktor: Funkce vytvoří a inicializuje tabulku.
 * 
 * @param t tabulka, jejíž prvky mají být spočteny
 * @return počet prvků tabulky (.size)
 */
size_t htab_size(const htab_t *t) {
    return t->size;
}