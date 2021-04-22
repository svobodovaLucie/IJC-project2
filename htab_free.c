// htab_free.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Destruktor: funkce zruší všechny prvky tabulky a uvolní alokovanou paměť.
 * 
 * @param t tabulka ke zrušení
 * @return void
 */
void htab_free(htab_t * t) {
    htab_clear(t);
    free(t);
}
