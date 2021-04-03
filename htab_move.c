#include "htab.h"
#include "htab_structs.h"

// t=htab_move(newnumb,t2)

// move konstruktor: vytvoření a inicializace
// nové tabulky přesunem dat z tabulky t2,
// t2 nakonec zůstane prázdná a alokovaná
// (tuto funkci cvičně použijte v programu
// podmíněným překladem #ifdef MOVETEST)

/**
 * @brief move konstruktor: vytvoření a inicializace nové tabulky přesunem dat z tabulky t2, t2 nakonec zůstane prázdná a alokovaná
 * 
 * @param n 
 * @param from
 * @return 
 */
htab_t *htab_move(size_t n, htab_t *from) {
    htab_t *new = htab_init(n);

    // presun dat z from do new (vyuzit lookup_add pravdepodobne)

    //htab_clear(from);
}