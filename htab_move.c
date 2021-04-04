#include "htab.h"
#include "htab_structs.h"

/**
 * @brief move konstruktor: vytvoření a inicializace nové tabulky přesunem dat z tabulky t2, t2 nakonec zůstane prázdná a alokovaná
 * 
 * @param n velikost pole ukazatelu v nove tabulce
 * @param from tabulka, ze ktere se maji data zkopirovat
 * @return nove alokovana a naplnena tabulku
 */
htab_t *htab_move(size_t n, htab_t *from) {
    htab_t *new = htab_init(n);
    for (size_t i = 0; i < from->arr_size; i++) {
        for (htab_item_t *item = from->arr[i]; item != NULL; item = item->next) {
            htab_pair_t *pair_new = htab_lookup_add(new, item->pair.key);
            if (pair_new == NULL) {
                return NULL;
            }
            htab_pair_t *pair_from = htab_find(from, item->pair.key);
            if (pair_from == NULL) {
                return NULL;
            }
            pair_new->value = pair_from->value;
        }
    }
    htab_clear(from);
    return new;
}