#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "htab_structs.h"

// htab_free(t)
/**
 * @brief destruktor: zrušení tabulky (volá htab_clear())
 * 
 * @param t tabulka ke zrušení
 * @return void
 */
void htab_free(htab_t * t) {
    htab_clear(t);
    free(t);
    printf("I am freed!\n");
}