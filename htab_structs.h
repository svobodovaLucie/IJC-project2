#ifndef __HTAB_STRUCT_H__
#define __HTAB_STRUCT_H__

#include "htab.h"

// Tabulka je (pro knihovnu privátní) struktura obsahující pole seznamů a jeho velikost
/* 
      +----------+
      | size     | // aktuální počet záznamů [(key,data),next]
      +----------+
      | arr_size | // velikost následujícího pole ukazatelů
      +----------+
      +---+
      |ptr|-->[(key,data),next]-->[(key,data),next]-->[(key,data),next]--|
      +---+
      |ptr|--|
      +---+
      |ptr|-->[(key,data),next]-->[(key,data),next]--|
      +---+
      |ptr|--|
      +---+
*/
struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};

// Záznam [(key,value),next]
typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

#endif // __HTAB_STRUCT_H__