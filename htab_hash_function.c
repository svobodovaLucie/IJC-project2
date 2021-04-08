// htab_hash_function.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0
// Funkce převzata ze zadání úkolu

#include <stdint.h>
#include "htab.h"
/**
 * @brief Hashovací funkce.
 * 
 * @param str Řetězec k zaheshování
 * @return výsledek hashovací funkce
 */
size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}
