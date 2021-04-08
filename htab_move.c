// htab_move.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_structs.h"
/**
 * @brief Move konstruktor: funkce vytvoří a inicializuje novou tabulku přesunem dat z tabulky from
 *        tabulka from nakonec zůstane prázdná a alokovaná
 * 
 * @param n velikost pole ukazatelů v nové tabulce
 * @param from tabulka, ze které se mají data zkopírovat
 * @return nově alokovaná a naplněná tabulka
 */
htab_t *htab_move(size_t n, htab_t *from) {
    htab_t *new = htab_init(n);
    if (new == NULL) {  // nedostatek paměti pro alokaci nové tabulky
        return NULL;
    }
    // průchod tabulkou from a postupné přidávání prvků do nové tabulky
    for (size_t i = 0; i < from->arr_size; i++) {
        for (htab_item_t *item = from->arr[i]; item != NULL; item = item->next) {
            htab_pair_t *pair_new = htab_lookup_add(new, item->pair.key);
            if (pair_new == NULL) {
                htab_free(new);
                return NULL;
            }
            htab_pair_t *pair_from = htab_find(from, item->pair.key);
            if (pair_from != NULL) {
                pair_new->value = pair_from->value;
            }
        }
    }
    htab_clear(from);
    return new;
}