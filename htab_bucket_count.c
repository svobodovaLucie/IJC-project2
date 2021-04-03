#include "htab.h"
#include "htab_structs.h"

// size_t n=htab_bucket_count(t)

/**
 * @brief funkce vraci počet prvků pole tabulky t (.arr_size)
 * 
 * @param t tabulka, ve ktere se ma zaznam vyhledat
 * @return počet prvků pole (.arr_size)
 */
size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}
