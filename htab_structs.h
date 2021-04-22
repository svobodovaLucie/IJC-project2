// htab_structs.h
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0
// Definice privátních struktur knihovny htab.h

#ifndef __HTAB_STRUCT_H__
#define __HTAB_STRUCT_H__

#include "htab.h"

/**
 *  Tabulka je (pro knihovnu privátní) struktura obsahující pole seznamů a jeho velikost
 */
struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};

/**
 *  Záznam [(key,value),next]
 */
typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

#endif // __HTAB_STRUCT_H__
